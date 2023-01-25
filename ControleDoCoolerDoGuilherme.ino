/*

SALAMAKER
Controlando um LED e lendo um LDR por uma página web com D1 - Wemos - ESP8266 */

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

uint8_t relayOn[] = {0xA0, 0x01, 0x00, 0xA1};
uint8_t relayOff[] = {0xA0, 0x01, 0x01, 0xA2};

#include <ESP8266WiFi.h>

const char* ssid = "Anne 2G";
const char* password = "bangu329";

IPAddress ip(192,168,0,100);
IPAddress gateway(192,168,0,1); 
IPAddress subnet(255,255,255,0);

 int estado_led = 0; //desligado

ESP8266WebServer server(80); //Objeto "servidor" na porta 80(porta HTTP)


void setup() {

  Serial.begin(9600);
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);

 
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) //Aguarda a conexao
  {
    Serial.print("Estabelecendo conexão com ");
    Serial.println(WiFi.SSID()); //Imprime o nome da rede
    delay(500);
  }
  Serial.print("Conectado a rede! Endereco IP ESP -> ");
  Serial.println(WiFi.localIP()); //Imprime o IP local do ESP

  
  /* Cria a associacao entre endereço HTML as funções que serão utilizadas */
  server.on("/", paginaInicial);
 
  server.begin(); //Inicia o servidor
  
}

void loop() {
  //Analise das solicitacoes via web
  server.handleClient();
}

void paginaInicial()
{

  //============================
   String htmlMessage = "<!DOCTYPE html>"
                             "<html>"
                             "<head>"
                             "<meta http-equiv=\"refresh\" content=\"1\">" //Atualizar a pagina a cada 1s"
                             "<style>html{margin: 0px auto; text-align: center;}"
                             ".botao_liga{background-color: #00FF00; color: white; padding: 15px 40px ; border-radius: 25px;}"
                             ".botao_desliga{background-color: #FF0000; color: white; padding: 15px 40px; border-radius: 25px;}</style></head>"
                             "<title>Controle do Cooler do Guilherme</title>"
                             "<body><h1>Controle da ventoinha do PC do Guilherme</h1>"
                             "<a href=\"/?ledstatus=0\"><button class=\"botao_liga\">LIGA</button></a>"
                             "<a href=\"/?ledstatus=1\"><button class=\"botao_desliga\">DESLIGA</button></a>";
                             
                             if(estado_led == 0){ 
                               if(server.arg("ledstatus")=="0"){
                                 Serial.write(relayOn, 4);
                                 estado_led=1;
                               }
                             }else{
                               
                               if(server.arg("ledstatus")=="1"){
                                 Serial.write(relayOff, 4);
                                 estado_led=0;
                               }
                             }
                             "</body>"
                             "</html>";
                             

  //============================
  server.send(200, "text/html", htmlMessage); //Retorna resposta HTTP
}


