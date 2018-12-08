// Alison Palmer and Anusha Datar
// Impedance and Antenna analysis circuit
// RF transmitter used: https://www.sparkfun.com/products/10534

#include <VirtualWire.h>

// TX pin for radio.
int radio_tx_pin = 2;
int antenna_voltage_pin = A0;
int transmitter_voltage_pin = A1;

void setup()
{
  Serial.begin(9600); 
  Serial.println("Initializing TX");

  vw_set_ptt_inverted(true); 
  vw_setup(2000);     // bps
  vw_set_tx_pin(radio_tx_pin);        

  // Source and load voltage measurement pins.
  pinMode(antenna_voltage_pin, INPUT);
  pinMode(transmitter_voltage_pin, INPUT);
  // LEDs are good.
  pinMode (13, OUTPUT);
}

void loop()
{
  // Transmitter code for radio module. Comment out for standard impedance matching, or leave for increased delay.
  digitalWrite(13, true);  // Status LEDs are important.
  char *msg = "1"; // The message to send over the air.
  vw_send((uint8_t *)msg, strlen(msg));
  vw_wait_tx(); 
  digitalWrite(13, false);

  int transmitter_value = analogRead(transmitter_voltage_pin);
  Serial.print("\nTransmitter value : "); 
  Serial.print(transmitter_value);
  int antenna_value = analogRead(antenna_voltage_pin);
  Serial.print("\nAntenna value : ");
  Serial.print((antenna_value));
}
