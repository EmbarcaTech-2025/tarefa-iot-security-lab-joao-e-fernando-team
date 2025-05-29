/*! ============================================================================
 *
 *  Copyright(c) 2025 JV Gomes. All rights reserved.
 *
 *  Laboratorio de Seguranca IOT
 *  @brief  Autenticação, criptografia e proteção contra ataques em comunicação
 *          MQTT com a BitDogLab.
 *
 *  @file	    iot_security_lab.c
 *  @author     Joao Vitor G. de Oliveira
 *  @date	    25 Maio 2025
 *  @version    v1.0
 * 
============================================================================ */
/* 
 * Comandos de terminal para testar o MQTT:
 * 
 * Inicia o broker MQTT com logs detalhados:
 * mosquitto -c mosquitto.conf -v
 * 
 * Assina o tópico de temperatura (recebe mensagens):
 * mosquitto_sub -h 192.168.137.1 -p 1883 -t "test/temp" -u "BitDogLab" -P "senha123"
 * 
 * Publica mensagem de teste no tópico de temperatura:
 * mosquitto_pub -h 192.168.137.1 -p 1883 -t "test/temp" -u "BitDogLab" -P "senha123" -m "teste"
 */
/* ============================   LIBRARIES  =============================== */
#include <string.h>                 // Para funções de string como strlen()
#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"            // Biblioteca padrão do Pico (GPIO, tempo, etc.)
#include "pico/cyw43_arch.h"        // Driver WiFi para Pico W
#include "include/wifi_conn.h"      // Funções personalizadas de conexão WiFi
#include "include/mqtt_comm.h"      // Funções personalizadas para MQTT
#include "include/xor_cipher.h"     // Funções de cifra XOR
#include <time.h>

/* =============================   MACROS   ================================ */

#define LED_RED_PIN 13 
#define LED_BLUE_PIN 12     
#define LED_GREEN_PIN 11   

/* =========================   GLOBAL VARIABLES   ========================== */
// Credenciais para conexão no wifi
const char SSID[] = {"VIRUS"};
const char PASSWORD[] = {"Jvgdo123"};

// Credenciais para conexão no broker
const char BROKER_IP[] = {"192.168.137.1"};
const char USER[] = {"BitDogLab"};
const char PASS[] = {"senha123"};


/* ========================   FUNCTION PROTOTYPE   ========================= */
void gpio_start(void);
void send_info(void);

/* ===========================   MAIN FUNCTION   =========================== */
int main(void)
{
    uint64_t time=0;
    // Inicializa todas as interfaces de I/O padrão (USB serial, etc.)
    stdio_init_all();

    gpio_start();
    
    // Conecta à rede WiFi
    // Parâmetros: Nome da rede (SSID) e senha
    connect_to_wifi(SSID, PASSWORD);

    // Configura o cliente MQTT
    // Parâmetros: ID do cliente, IP do broker, usuário, senha
    // mqtt_setup("bitdog1", "IP do broker", "aluno", "senha123");

    // // Pubblisher
    // mqtt_setup("bitdog_JV", BROKER_IP, USER, PASS);

    // Subscribe
    mqtt_setup("bitdog_FF", BROKER_IP, USER, PASS);

    // Mensagem original a ser enviada
    const char *mensagem = "26.5"; 

    // Buffer para mensagem criptografada (16 bytes)
    uint8_t criptografada[50];

    // Criptografa a mensagem usando XOR com chave 42
    xor_encrypt((uint8_t *)mensagem, criptografada, strlen(mensagem), 42);

    // Loop principal do programa
    while (true) 
    {
        time = get_absolute_time();
        char buffer[40]={};
        sprintf(buffer,"{\"valor\":26.5,\"ts\":%lu}",time);

        //  Publica a mensagem original (não criptografada)
        //mqtt_comm_publish("test/temp", mensagem, strlen(mensagem));

        // Alternativa: Publica a mensagem criptografada sem proteção de replay
        //mqtt_comm_publish("test/temp", criptografada, strlen(criptografada));

        // Mesagem para proteção contra replay sem criptografia
        //mqtt_comm_publish("test/temp", buffer, strlen(buffer));

        // Mensagem com proteção contra Replay criptografada
        xor_encrypt((uint8_t *)buffer, criptografada, strlen(buffer), 42);
        mqtt_comm_publish("test/temp", criptografada, strlen(criptografada));
        
        // Aguarda 5 segundos antes da próxima publicação
        sleep_ms(3000);
        send_info();
    }
    return 0;
} /* end main */

/* =======================  DEVELOPMENT OF FUNCTIONS ======================= */
void gpio_start(void)
{
    gpio_init(LED_RED_PIN);
    gpio_set_dir(LED_RED_PIN, GPIO_OUT);
    
    gpio_init(LED_GREEN_PIN);
    gpio_set_dir(LED_GREEN_PIN, GPIO_OUT);
    
    gpio_init(LED_BLUE_PIN);
    gpio_set_dir(LED_BLUE_PIN, GPIO_OUT);

    // Desligando os LEDs no início
    gpio_put(LED_RED_PIN, false);
    gpio_put(LED_GREEN_PIN, false);
    gpio_put(LED_BLUE_PIN, false);
}

void send_info(void)
{
    printf ("mesnagem enviada");
    
    gpio_put(LED_BLUE_PIN, true);
    sleep_ms(100);
    gpio_put(LED_BLUE_PIN, false);
}

/* end program */
