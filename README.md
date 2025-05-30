[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/G8V_0Zaq)

# Tarefa: IoT Security Lab - EmbarcaTech 2025

Autor: João Vitor Gomes e Ferando Furtado

Curso: Residência Tecnológica em Sistemas Embarcados

Instituição: EmbarcaTech - HBr

Brasilia, maio de 2025

---

## Tema do Projeto:
Autenticação, criptografia e proteção contra ataques em comunicação MQTT com a BitDogLab.

---

## Relatos e Analise:
As seguintes técnicas aplicadas no projeto demonstram escalabilidade para ambientes com múltiplos dispositivos IoT:

#### MQTT com arquitetura publish/subscribe:
O protocolo MQTT é leve e eficiente, ideal para ambientes com múltiplos dispositivos. Sua arquitetura desacoplada permite que diversos dispositivos publiquem e assinem tópicos sem interferência mútua, facilitando a expansão da rede.

#### Autenticação com controle de acesso:
A utilização de autenticação básica no broker Mosquitto, através de arquivos de senha e controle de acesso, permite gerenciar múltiplos dispositivos de forma segura. Isso é essencial para ambientes com muitos dispositivos, como redes escolares.

#### Criptografia leve com XOR:
Embora simples, a criptografia XOR oferece uma camada adicional de segurança, dificultando a interceptação de dados por ferramentas como o Wireshark. Essa técnica é útil para proteger informações em ambientes com recursos limitados.

#### Proteção contra ataques de replay com timestamp
A inclusão de timestamps nas mensagens permite verificar a atualidade dos dados recebidos, prevenindo a reutilização de mensagens antigas por agentes maliciosos.

## Como aplicar essas técnicas com várias BitDogLab em rede:

#### Configuração de tópicos hierárquicos:
Utilize uma estrutura de tópicos que reflita a organização física da escola, como escola/sala1/temperatura. Isso facilita o gerenciamento e a identificação das mensagens por sala ou setor. Considere usar sempre o mesmo padrão para troca de mensagens

#### Gerenciamento centralizado do broker MQTT:
Implemente um broker centralizado, como o Mosquitto, em um servidor local ou na nuvem. Isso permite o controle e monitoramento de todas as BitDogLabs conectadas, além de facilitar a aplicação de políticas de segurança e autenticação.

#### Implementação de autenticação individualizada:
Atribua credenciais únicas para cada BitDogLab, permitindo o controle de acesso e a identificação de dispositivos específicos. Isso é crucial para manter a segurança e integridade da rede.

#### Automatização da criptografia e verificação de mensagens:
Integre a função de criptografia XOR ou metodos mais avançados e a verificação de timestamps diretamente no firmware das BitDogLabs. Isso garante que todas as mensagens sejam criptografadas e validadas automaticamente, sem intervenção manual.

#### Monitoramento e manutenção contínuos:
Estabeleça rotinas de monitoramento para verificar o funcionamento das BitDogLabs e a integridade das mensagens transmitidas. Isso pode incluir logs de atividade, alertas para falhas de comunicação e atualizações periódicas do firmware.

---

## 📜 Licença
GNU GPL-3.0.
