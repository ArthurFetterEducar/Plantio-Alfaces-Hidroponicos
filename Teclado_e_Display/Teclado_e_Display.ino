#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Configurações para o display OLED
#define SCREEN_WIDTH 128    // Largura do display em pixels
#define SCREEN_HEIGHT 64    // Altura do display em pixels
#define SCREEN_ADRESS 0X3C

// Criando objeto para o display
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Pinos teclado matricial 
#define TOTAL_LINHAS  1
#define TOTAL_COLUNAS 5

#define C1  12
#define C2  14
#define C3  13
#define C4  35
#define C5  34

// Struct para botões 
struct Teclado_btn {
  unsigned int C_pino;            // Coluna conectada ao botão
  unsigned int debounce;          // Debounce para o botão
  unsigned long debounce_time;    // Tempo para debounce do botão
  char caractere;              // Caractere do botão 
};

// Inicialização de todos os botões
struct Teclado_btn btn_entr = {C1, 1, 0, 'E'};
struct Teclado_btn btn_up = {C2, 1, 0, 'U'};
struct Teclado_btn btn_left = {C3, 1, 0, 'L'};
struct Teclado_btn btn_down = {C4, 1, 0, 'D'};
struct Teclado_btn btn_right = {C5, 1, 0, 'R'}; 

// Matriz para o teclado
struct Teclado_btn teclado[TOTAL_COLUNAS] = {btn_entr, btn_up, btn_left, btn_down, btn_right};

//Clock for debounce
#define DEBOUNCE_TIME  150000

char key_press(struct Teclado_btn *botao);  // Protótipo função key_press

// Variável gerais
char caractere = '\0'; // Caractere de retorno teclado matricial
unsigned int i = 0;  // Variável de indexação


void setup() 
{  
  // Setup pinos do teclado
  pinMode(C1, INPUT_PULLUP);
  pinMode(C2, INPUT_PULLUP);
  pinMode(C3, INPUT_PULLUP);
  pinMode(C4, INPUT_PULLUP);  // Resistor precisa ser adicionado manualmente
  pinMode(C5, INPUT_PULLUP);  // Resistor precisa ser adicionado manualmente

  // Setup comunicação serial
  Serial.begin(9600);

  // Setup display oled 
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  oled.clearDisplay();

  oled.setTextSize(2);
  oled.setTextColor(WHITE);
}

void loop() 
{  
  for (i = 0; i < TOTAL_COLUNAS; i++) {
    caractere = key_press(&teclado[i]);

    if (caractere != '\0') {
      break;
    }
  } 

  if (caractere != 0) {
    oled.clearDisplay();
    oled.setCursor(0, 10);
    oled.print(caractere);
    oled.display();
  }
}


char key_press(struct Teclado_btn *botao)
{
  char c = '\0';
  
  if (digitalRead(botao->C_pino) == 0 && botao->debounce == 1 && botao->debounce_time > DEBOUNCE_TIME) {
    c = botao->caractere;

    botao->debounce = 0; 
    botao->debounce_time = 0;     
  } 
  if (digitalRead(botao->C_pino) == 1) {
    botao->debounce = 1; 
  }

  botao->debounce_time++;

  return c;
}