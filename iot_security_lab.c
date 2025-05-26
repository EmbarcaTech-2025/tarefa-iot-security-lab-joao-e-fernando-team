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
 * mosquitto_sub -h localhost -p 1883 -t "test/temp" -u "aluno" -P "senha123"
 * 
 * Publica mensagem de teste no tópico de temperatura:
 * mosquitto_pub -h localhost -p 1883 -t "test/temp" -u "aluno" -P "senha123" -m "26.6"
 */
/* ============================   LIBRARIES  =============================== */
#include <string.h>                 // Para funções de string como strlen()
#include "pico/stdlib.h"            // Biblioteca padrão do Pico (GPIO, tempo, etc.)
#include "pico/cyw43_arch.h"        // Driver WiFi para Pico W
#include "include/wifi_conn.h"      // Funções personalizadas de conexão WiFi
#include "include/mqtt_comm.h"      // Funções personalizadas para MQTT
#include "include/xor_cipher.h"     // Funções de cifra XOR

/* =============================   MACROS   ================================ */

/* =========================   GLOBAL VARIABLES   ========================== */
// Credenciais para conexão no laboratorio do FINATEC
const char SSID[] = {"AP-ACCESS BLH"};
const char PASSWORD[]={"Fin@ApointBlH"};

// // Credenciais para conexão em rede privada
// const char SSID[] = {"JV_HOUSE_5G"};
// const char PASSWORD[] = {"387220360"};


const char BROKER_IP[] = {"172.19.8.60"};

/* ========================   FUNCTION PROTOTYPE   ========================= */


/* ===========================   MAIN FUNCTION   =========================== */
int main(void)
{
    // Inicializa todas as interfaces de I/O padrão (USB serial, etc.)
    stdio_init_all();

    // Conecta à rede WiFi
    // Parâmetros: Nome da rede (SSID) e senha
    connect_to_wifi(SSID, PASSWORD);

    // Configura o cliente MQTT
    // Parâmetros: ID do cliente, IP do broker, usuário, senha
    //mqtt_setup("bitdog1", "IP do broker", "aluno", "senha123");

    mqtt_setup("bitdog1", BROKER_IP, NULL, NULL);

    // Mensagem original a ser enviada
    const char *mensagem = "26.5";
    // Buffer para mensagem criptografada (16 bytes)
    uint8_t criptografada[16];
    // Criptografa a mensagem usando XOR com chave 42
    xor_encrypt((uint8_t *)mensagem, criptografada, strlen(mensagem), 42);

    // Loop principal do programa
    while (true) 
    {
        // Publica a mensagem original (não criptografada)
        mqtt_comm_publish("test/temp", mensagem, strlen(mensagem));
        
        // Alternativa: Publica a mensagem criptografada (atualmente comentada)
        // mqtt_comm_publish("escola/sala1/temperatura", criptografada, strlen(mensagem));
        
        // Aguarda 5 segundos antes da próxima publicação
        sleep_ms(5000);
    }
    return 0;
} /* end main */

/* =======================  DEVELOPMENT OF FUNCTIONS ======================= */


/* end program */
