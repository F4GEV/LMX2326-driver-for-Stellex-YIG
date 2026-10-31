

//fvco = [(P x B) + A] x fosc/R
//fvco: Output frequency of external voltage controlled oscillator (VCO)
//B: Preset divide ratio of binary 13-bit programmable counter (3 to 8191)
//A: Preset divide ratio of binary 5-bit swallow counter (0 <= A <= 31; A <= B for LMX2316/26)
//or (0 <= A <= 7, A <= B for LMX2306)
//fosc: Output frequency of the external reference frequency oscillator
//R: Preset divide ratio of binary 14-bit programmable reference counter (3 to 16383)
//P: Preset modulus of dual modulus prescaler
//for the LMX2306; P = 8 for the LMX2316/26; P = 32


 //
 //
 // diviseur /4 sur la carte PLL
 // Mini 8.1000 GHz
 // Maxi 10.200 GHz
 //
 // Calculated by Code Loader 4 software boucle de phase 1 Mhz
 // R = 1 MHz // R_Reg = 0x0000028
 // 0x0801FA5 => 8.1000 GHz - 0x0802329 => 9.0000 GHz - 0x0802711 => 10.0000 GHz
 //
 // Calculated by Code Loader 4 software boucle de phase 250 Khz
 // R = 250 KHz // R_Reg = 0x00000A0 // Meilleur sur les epaules latérales du signal CW
 // 0x0807E91 => 8.1000 GHz - 0x0808CA1 => 9.0000 GHz - 0x0809C41 => 10.0000 GHz  - 0x0809F61 => 10.2000 GHz
 //
  unsigned long R_Reg = 0x00000A0; // Diviser PLL
  unsigned long N_Reg = 0x0807E91; // Frequence par défaut
  unsigned long F_Reg = 0x0000682;

//

  unsigned long DTA;
  int bp;
  const int LE = 4;
  const int DATA = 2; //old 2
  const int CLK = 3;  //old 3

void setup() {       
  pinMode (LE, OUTPUT);  // latch enable
  pinMode (CLK, OUTPUT);  // clock
  pinMode (DATA, OUTPUT);  // data
  
  digitalWrite(LE,LOW);
  digitalWrite(CLK,LOW);

// port série
Serial.begin(9600);
//Serial1.begin(9600);

  // to loop for testing uncomment 3 lines below
////while(true) { // TEST While to loop for scope
  
 DTA = R_Reg;    // Send setup parameters
 SendWord();
 DTA = N_Reg;
 SendWord();
 DTA = F_Reg;
 SendWord();
 

}

void loop() {  // loop forever

char teststr='A';
//
//Serial.print("LMX2326 driver ");
//Serial.println("-------------- ");
//Serial.println(" ");
//Serial.println("PLL Loop 250 kHz ");
//Serial.println(" ");
//Serial.println("A = 8.1000 GHz ");
//Serial.println("B = 9.0000 GHz GHz ");
//Serial.println("C = 10.0000 GHz GHz ");
//Serial.println("D = 10.2000 GHz GHz ");
//Serial.println(" ");
//Serial.println("Entrer la lettre : ");
//
  while (Serial.available() == 0) {}     //wait for data available
  teststr = Serial.read();  //read until timeout
  //teststr.trim();      // remove any \r \n whitespace at the end of the String
switch (teststr) {
 
    case 'A':
        Serial.println("Frequence 8.1 GHz !!!");
        N_Reg = 0x0807E91; // Frequence 8.1 GHz
         DTA = R_Reg;    // Send setup parameters
          SendWord();
         DTA = N_Reg;
          SendWord();
        DTA = F_Reg;
          SendWord();
      break;
 
    case 'B':
        Serial.println("Frequence 9.0 GHz !!!");
        N_Reg = 0x0808CA1; // Frequence 9.0 GHz
         DTA = R_Reg;    // Send setup parameters
          SendWord();
         DTA = N_Reg;
          SendWord();
        DTA = F_Reg;
          SendWord();
      break;

    case 'C':
        Serial.println("Frequence 10.0 GHz !!!");
        N_Reg = 0x0809C41; // Frequence 10 GHz
         DTA = R_Reg;    // Send setup parameters
          SendWord();
         DTA = N_Reg;
          SendWord();
        DTA = F_Reg;
          SendWord();
      break;

    case 'D':
         Serial.println("Frequence 10.2 GHz !!!");    
         N_Reg = 0x0809F61; // Frequence 10.2 GHz
         DTA = R_Reg;    // Send setup parameters
          SendWord();
         DTA = N_Reg;
          SendWord();
        DTA = F_Reg;
          SendWord();
      break;
     
  }



}


// --------------------------------------------------------


int SendWord() 
{
  bp = 21;
  do
  {
  bp = bp - 1;   //loop through bit positions 22 to 0
  digitalWrite(CLK,LOW); 
  digitalWrite(DATA, bitRead(DTA,bp) ); 
  digitalWrite(CLK,HIGH); 
  }
  while(bp>0);
  
  digitalWrite(CLK,LOW); 
  digitalWrite(DATA,LOW);

  digitalWrite(LE,HIGH);   // Set LE to latch data
  delayMicroseconds(4);
  digitalWrite(LE,LOW);

}