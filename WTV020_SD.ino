//Exemplo: Modulo WTV020-SD com Arduino
//Visite: https://blog.eletrogate.com/

//Inclui biblioteca
#include <Wtv020sd16p.h>

#define DIN_PIN 4   //Pino DI
#define BUSY_PIN 5  //Pino busy
#define RST_PIN 2  //Pino Reset
#define CLK_Pin 3  //Pino clock

 
//Buffer de armazenamento
char bufferRead;

//Inicializa objeto com os pinos utilizados na montagem
Wtv020sd16p wtv020sd16p(RST_PIN,CLK_Pin,DIN_PIN,BUSY_PIN);
 
void setup()
{
  //Inicializa a porta serial serial
  Serial.begin(9600);
  //Inicializa o modulo WTV020
  wtv020sd16p.reset();
}
 
void loop()
{
  Serial.println("Para reproduzir o arquivo ad4.ad4 digite a");
  Serial.println("Para reproduzir o arquivo mps.mp3 digite b");
  Serial.println();
  
  //Aguarda receber algum byte na porta serial
  do
  {
    delay(1000);
      if(Serial.available())
      {
        bufferRead = Serial.read();
        
        if (bufferRead == 'a')
        {
          TocaAudio(1);
          break;
        }
          
         
        //Caso seja recebido o numero 2, reproduz o arquivo 0002.ad4
        if (bufferRead == 'b')
        {
          TocaAudio(2);
          break;
        }
      }
  }while(1);
  
}

void TocaAudio(int i)
{
  Serial.println("tocando: ");
  Serial.print(i);
  wtv020sd16p.playVoice(2);
  wtv020sd16p.asyncPlayVoice(i);
  delay(5000); 
  wtv020sd16p.stopVoice();
  delay(1000); 
}