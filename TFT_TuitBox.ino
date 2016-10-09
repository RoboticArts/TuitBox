#include <Adafruit_GFX.h>  // Libreria de gráficos
#include <Adafruit_TFTLCD.h>  //Libreria LCD
#include <TouchScreen.h>     // Libreria del panel tactil

// 320×240 pixeles


// Pines necesarios para los 4 pines del panel tactil
#define YP A1 // Pin analogico A1 para ADC
#define XM A2 // Pin analogico A2 para ADC
#define YM 7 
#define XP 6 

// Definimos la presion máxima y minima que podemos realizar sobre el panel
#define MINPRESSURE 1
#define MAXPRESSURE 1000

// Para mejor precision de la presion realizada, es necesario 
// medir la resistencia entre los pines X+ y X-.
// En Shield TFT 2.4" LCD se mide entre los pines A2 y 6
// Instancia del panel tactil (Pin XP, YP, XM, YM, Resistencia del panel) 
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 364); 

short TS_MINX = 150; // Coordenadas del panel tactil para delimitar
short TS_MINY = 120; // el tamaño de la zona donde podemos presionar
short TS_MAXX = 850; // y que coincida con el tamaño del LCD
short TS_MAXY = 891; 

// Pines de conexion del LCD 
#define LCD_CS A3 // Chip Select - Pin analogico 3
#define LCD_CD A2 // Command/Data - Pin Analogico 2
#define LCD_WR A1 // LCD Write - Pin Analogico 1
#define LCD_RD A0 // LCD Read - Pin Analogico 0
#define LCD_RESET A4 // LCD Reset - Pin Analogico 4


Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET); // Instancia del LCD 

int X; // Variables que almacenaran la coordenada
int Y; // X, Y donde presionemos y la variable Z 
int Z; // almacenara la presion realizada

int a = 0; // variable "flag" para control rebotes

#define ledA 5
#define ledK 3

#define WHITE   0x0000  // Definimos los colores para poder referirnos a ellos con su nombre                  
#define CYAN     0xF800  // en lugar de usar el código hexadecimal de cada uno. 
#define MAGENTA   0x07E0 
#define BLACK   0xFFFF  
#define YELLOW    0x001F 
#define RED    0x07FF
#define BLUE  0xFFE0
#define GREEN 0xF81F




void setup(void) 
{
  tft.begin(0x9341); // Iniciamos el LCD especificando el controlador de nuestro LC. En este caso el ILI9341. 
                     // Otros controladores: 0x9325, 0x9328,0x7575, 0x9341, 0x8357.

  tft.fillScreen(BLACK); // Colocamos el fondo del LCD en Negro
    
  pinMode(13, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);

  tft.drawRect(40, 20, 160, 60, RED); // Dibujamos un "boton"
  
  tft.setCursor(60,35);  // Colocamos el cursor
  tft.setTextSize(4);    // Especificamos el tamaño del texto
  tft.setTextColor(RED); // Definimos el color del texto 
  tft.println("BOTON"); // Escribimos por pantalla    
}

void loop(){

  //tft.setRotation(2);
  /*
  tft.setCursor(40,80);
  tft.setTextSize(4);
  tft.setTextColor(CYAN);
  tft.println("TWITTER");
  delay(500);
  
  tft.setCursor(40,150);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.println("Iniciando...");
  delay(500);
  
  tft.setCursor(40,180);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.println("Cargando...");
  delay(500);


  tft.setCursor(40,210);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.println("Conectando...");
  delay(500);

  
  tft.setCursor(80,240);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.println("¡EXITO!");
  delay(500);
*/
  //Wifi_Connect();

   lecturaPanel(); // Realizamos lectura del panel para detectar presion y coordenadas
      
    // Si la pulsación del eje X se produce entre los puntos 40 y 160
    // Y la pulsacion del eje Y se produce entre los puntos 20 y 60
    // Y la presión realizada esta entre el margen determinado
    if((X > 40 && X < 200) && (Y > 20 && Y < 60) && (Z > MINPRESSURE && Z < MAXPRESSURE)) 
    {
      if (a == 0) // Si la variable flag esta en 0
      {
        tft.fillRect(40, 20, 160, 60, RED); // Dibujamos nuestro boton relleno de color
        
        tft.setCursor(70,25); // Colocamos el cursor
        tft.setTextSize(3);   // Especificamos el tamaño del texto
        tft.setTextColor(WHITE); // Definimos el color del texto 
        tft.println("BOTON"); // Escribimos por pantalla
        tft.setCursor(60,50);  // Colocamos el cursor
        tft.println("PULSADO"); // Escribimos por pantalla   
     
        digitalWrite(ledA, HIGH);
        digitalWrite(ledK, LOW);

        a = 1; // Ponemos la variable flag en 1
        delay(150);
      }
      else if (a == 1) // Si la variable flag esta en 1
      {
         tft.fillRect(41, 21, 158, 58, CYAN); // Dibujamos el fondo de nuestro boton en cyan
         
         tft.setCursor(60,35); // Colocamos el cursor
         tft.setTextSize(4); // Especificamos el tamaño del texto
         tft.setTextColor(RED); // Definimos el color del texto 
         tft.println("BOTON"); // Escribimos por pantalla
         
        digitalWrite(ledA, LOW);
        digitalWrite(ledK, LOW);
         
         a = 0; // Ponemos la variable flag en 0 para evitar los rebotes
         delay(150);
      }
    }    
  
}


void Wifi_Connect(){
    
  tft.setCursor(80,20);
  tft.setTextSize(3);
  tft.setTextColor(WHITE);
  tft.println("WIFI");

  tft.fillRect(20, 50, 200, 30, WHITE);

  tft.setCursor(25,60);
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.println("ONO7373");

// Diferencia de 70
  tft.setCursor(80,90);
  tft.setTextSize(3);
  tft.setTextColor(WHITE);
  tft.println("CLAVE");

  tft.fillRect(20, 120, 200, 30, WHITE);

  tft.setCursor(25,130);
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.println("1234");

  teclado();
  tocar_teclado();
  }

void teclado(){
  
  int rel_Y = 30; // Coordenada relativa Eje Y
  int radius = 0;
  int y = 0, x = 0, width = 17;


  // Primera fila
  x = 8;
  y = 160 + rel_Y;
  
  tft.fillRoundRect(x, y,     width, 25, radius, WHITE); write_teclado('Q',x,y);
  tft.fillRoundRect(x+23, y,  width, 25, radius, WHITE); write_teclado('W',x+23,y);
  tft.fillRoundRect(x+46, y,  width, 25, radius, WHITE); write_teclado('E',x+46,y);
  tft.fillRoundRect(x+69, y,  width, 25, radius, WHITE); write_teclado('R',x+69,y);
  tft.fillRoundRect(x+92, y,  width, 25, radius, WHITE); write_teclado('T',x+92,y);
  tft.fillRoundRect(x+115, y, width, 25, radius, WHITE); write_teclado('Y',x+115,y);
  tft.fillRoundRect(x+138, y, width, 25, radius, WHITE); write_teclado('U',x+138,y);
  tft.fillRoundRect(x+161, y, width, 25, radius, WHITE); write_teclado('I',x+161,y);
  tft.fillRoundRect(x+184, y, width, 25, radius, WHITE); write_teclado('O',x+184,y);
  tft.fillRoundRect(x+207, y, width, 25, radius, WHITE); write_teclado('P',x+207,y);
  
  // Segunda fila
  x = 20;
  y = 190  + rel_Y;
  tft.fillRoundRect(x, y,     width, 25, radius, WHITE); write_teclado('A',x,y);
  tft.fillRoundRect(x+23, y,  width, 25, radius, WHITE); write_teclado('S',x+23,y);
  tft.fillRoundRect(x+46, y,  width, 25, radius, WHITE); write_teclado('D',x+46,y);
  tft.fillRoundRect(x+69, y,  width, 25, radius, WHITE); write_teclado('F',x+69,y);
  tft.fillRoundRect(x+92, y,  width, 25, radius, WHITE); write_teclado('G',x+92,y);
  tft.fillRoundRect(x+115, y, width, 25, radius, WHITE); write_teclado('H',x+115,y);
  tft.fillRoundRect(x+138, y, width, 25, radius, WHITE); write_teclado('J',x+138,y);
  tft.fillRoundRect(x+161, y, width, 25, radius, WHITE); write_teclado('K',x+161,y);
  tft.fillRoundRect(x+184, y, width, 25, radius, WHITE); write_teclado('L',x+184,y);

  // Tercera fila
  x = 43;
  y = 220  + rel_Y;
  tft.fillRoundRect(x, y,     width, 25, radius, WHITE); write_teclado('Z',x,y);
  tft.fillRoundRect(x+23, y,  width, 25, radius, WHITE); write_teclado('X',x+23,y);
  tft.fillRoundRect(x+46, y,  width, 25, radius, WHITE); write_teclado('C',x+46,y);
  tft.fillRoundRect(x+69, y,  width, 25, radius, WHITE); write_teclado('V',x+69,y);
  tft.fillRoundRect(x+92, y,  width, 25, radius, WHITE); write_teclado('B',x+92,y);
  tft.fillRoundRect(x+115, y, width, 25, radius, WHITE); write_teclado('N',x+115,y);
  tft.fillRoundRect(x+138, y, width, 25, radius, WHITE); write_teclado('M',x+138,y);

  //Barra espaciadora
  x = 66;
  y = 250  + rel_Y;
  tft.fillRect(x, y, 110, 25, WHITE);
  

  //Borrar
  x = 43;
  y = 227 + rel_Y;
  tft.fillRect(x+161, y, width*2-3, 25*2-10, WHITE);
  tft.setCursor(x+166,y+4);
  tft.setTextSize(4);
  tft.setTextColor(BLUE);
  tft.println("X");

  //Enviar
   x = 8;
   y = 227 + rel_Y;
   tft.fillRect(x, y, width*2-3, 25*2-10, WHITE);
   tft.setCursor(x+6,y+4);
   tft.setTextSize(4);
   tft.setTextColor(BLUE);
   tft.println("E");
}

void write_teclado(char letra, int X, int Y){
  
  tft.setCursor(X+1,Y+1);
  tft.setTextSize(3);
  tft.setTextColor(BLUE);
  tft.println(letra);

  }

void tocar_teclado(){
  
  
  }

void lecturaPanel()
{
    digitalWrite(13, HIGH); 
    TSPoint p = ts.getPoint(); // Realizamos lectura de las coordenadas
    digitalWrite(13, LOW);
  
    pinMode(XM, OUTPUT); // La librería utiliza estos pines como entrada y salida
    pinMode(YP, OUTPUT); // por lo que es necesario declararlos como salida justo
                         // despues de realizar una lectura de coordenadas.    
  
    // Mapeamos los valores analogicos leidos del panel tactil (0-1023)
    // y los convertimos en valor correspondiente a la medida del LCD 320x240
    X = map(p.x, TS_MAXX, TS_MINX, tft.width(), 0);
    Y = map(p.y, TS_MAXY, TS_MINY, tft.height(), 0);
    Z = p.z;
}
