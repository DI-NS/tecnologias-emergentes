int ledverde = 3;
int ledama = 5;
int ledrojo = 7;
int botao = 9;
bool estadoAnteriorBotao = HIGH; // Estado anterior do botão
bool transicao = false;          // Variável para gerenciar a transição entre os LEDs

void setup() {
    pinMode(ledverde, OUTPUT);
    pinMode(ledama, OUTPUT);
    pinMode(ledrojo, OUTPUT);
    pinMode(botao, INPUT_PULLUP); // Resistor pull-up interno

    Serial.begin(9600); // Inicia comunicação serial

    digitalWrite(ledverde, HIGH); // Inicializa LED verde ligado
    digitalWrite(ledama, LOW);
    digitalWrite(ledrojo, LOW);
}

void loop() {
    int estadoBotao = digitalRead(botao);

    if (estadoBotao == LOW && estadoAnteriorBotao == HIGH) {
        transicao = true;
        // Envia mensagem para o PC quando o botão for pressionado
        Serial.println("Solicitacao de travessia registrada");
    }

    if (transicao) {
        // Sequência de LEDs
        digitalWrite(ledverde, LOW);
        digitalWrite(ledama, HIGH);
        delay(3000);

        digitalWrite(ledama, LOW);
        digitalWrite(ledrojo, HIGH);
        delay(3000);

        digitalWrite(ledrojo, LOW);
        digitalWrite(ledverde, HIGH);

        transicao = false;
    }

    estadoAnteriorBotao = estadoBotao;
}
