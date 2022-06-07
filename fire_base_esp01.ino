#include <Firebase.h>
#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>
#include <ESP8266WiFi.h>

// Defindo dados do Firebase
// FIREBASE_HOST é o link de acesso sem o htpps:// do inicio e a / do final
// FIREBASE_AUTH é a chave de acesso: Configurações do projeto/Contas de Serviço/Chaves secretas do banco de dados
#define FIREBASE_HOST  "rvm-cefet-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "s048Hs5H63sIPXooVCWgmgXnIfWCz38dWhuuGdhk"
// Defindo dados da rede WiFi
// WIFI_SSID é o nome da rede
//WIFI_PASSWORD é a senha da rede
#define WIFI_SSID "VIVOFIBRA-04C1"
#define WIFI_PASSWORD "oFqfE5bvsm"

void setup() {
  Serial.begin(9600);

  // Criação do objeto e conexão a rede Wifi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  // Criação e inicialização da comunicação com o Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

// Criação da variável do tipo String
String cpf = "";
void loop() {
  // Identificação do usuário
  if (Serial.available()) {
    cpf = Serial.readString();
    // Solicitação via getInt para obter a pontuação do usuário
    int valor = Firebase.getInt(cpf);
    // Se o cpf já existir, a variável "valor" será a pontuação,
    // caso não exista, o método getInt irá criar um elemento com
    // a chave igual a variável "cpf" e irá definir a pontuação
    // como zero

    // Ganho de pontos: Se a variável valor já foi obtida, a chave
    // cpf foi cadastrada, então pode-se implementar a pontuação do
    // usuário. Sendo assim, "novo_valor" recebe o "valor" + 1
    int novo_valor = valor + 1;
    Firebase.setInt(cpf, novo_valor);
    cpf = "";
    novo_valor = 0;
  }
  delay(500);
}
