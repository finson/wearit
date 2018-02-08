
#define XLED 4
#define YLED 5
#define ZLED 6
#define AUDIO_OUT 9

#define NOTE_A4  440
#define NOTE_A5  880
#define NOTE_A6  1760

int accPin[] = {A0, A1, A2};
int ledPin[] = {XLED, YLED, ZLED};
int audioOutPin = AUDIO_OUT;
int audioFreq[] = {NOTE_A4, NOTE_A5, NOTE_A6};
int acc[] = {0,0,0};

void setup(void) {
  Serial.begin(115200);
  
  // initialize LED pins as output and turn them off
  
  pinMode(LED_BUILTIN, OUTPUT);
  analogWrite(LED_BUILTIN, LOW);

  for (int i = 0; i<3; i++) {
    pinMode(ledPin[i], OUTPUT);  
    digitalWrite(ledPin[i], LOW);
  }

  // Initialize audio out pin
  
  pinMode(audioOutPin, OUTPUT);  
  noTone(audioOutPin);  
 
  Serial.println("Hello, flatland. ");
}

void loop(void) {

  int peakAXIS;

  // Find the axis with the biggest ACC value
  
  for (int i = 0; i<3; i++) {
    acc[i] = analogRead(accPin[i])-512;
    Serial.print(acc[i]);Serial.print(" ");
    if (abs(acc[i]) >= abs(acc[peakAXIS])) {
      peakAXIS = i;
    }
  }
  
  Serial.print(" (peak ACC is ");
  Serial.print(acc[peakAXIS]);
  Serial.print(" on pin ");
  Serial.print(ledPin[peakAXIS]);
  Serial.println(")");

  // Light the associated LED, etc
  
  for (int i = 0; i<3; i++) {
    if (i == peakAXIS) {
      digitalWrite(ledPin[i], HIGH);
    } else {
      digitalWrite(ledPin[i], LOW);
    }
    if (i == 2) {
      noTone(audioOutPin);
    } else {
      tone(audioOutPin, audioFreq[i],500);
    }
  }
}


