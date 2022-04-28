//Inicio
#include <EasyBuzzer.h>
int pin = 2;
int bandera;
void setup() {
  // put your setup code here, to run once:
  EasyBuzzer.setPin(pin);
  Serial2.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  EasyBuzzer.update();
  if(Serial2.available()){
    bandera = Serial2.read();
  }
  if(bandera == 1){
    inicio();
  }
  if(bandera == 2){
    menu();
  }
  if(bandera == 4){
    perder();
  }
  if(bandera == 5){
    ganar();
  }
  if(bandera == 3){
    batalla();
  }
}

void perder(){
    EasyBuzzer.singleBeep( 1046, 89.285625); //frecuencua, duracion
    delay(99.20625);
    delay(297.61875);
    EasyBuzzer.singleBeep( 1567, 89.285625);
    delay(99.20625);
    delay(297.61875);
    EasyBuzzer.singleBeep( 1975, 89.285625);
    delay(99.20625);
    delay(297.61875);
    EasyBuzzer.singleBeep( 1479, 89.285625);
    delay(99.20625);
    delay(297.61875);
    EasyBuzzer.singleBeep( 1046, 89.285625);
    delay(99.20625);
    delay(297.61875);
    EasyBuzzer.singleBeep( 1567, 89.285625);
    delay(99.20625);
    delay(297.61875);
    EasyBuzzer.singleBeep( 1975, 89.285625);
    delay(99.20625);
    delay(297.61875);
    EasyBuzzer.singleBeep( 1479, 89.285625);
    delay(99.20625);
    delay(297.61875);
    EasyBuzzer.singleBeep( 1046, 89.285625);
    delay(99.20625);
    delay(297.61875);
    EasyBuzzer.singleBeep( 1567, 89.285625);
    delay(99.20625);
    delay(297.61875);
    EasyBuzzer.singleBeep( 1975, 89.285625);
    delay(99.20625);
    delay(297.61875);
    EasyBuzzer.singleBeep( 1479, 89.285625);
    delay(99.20625);
    delay(297.61875);
    EasyBuzzer.singleBeep( 1046, 89.285625);
    delay(99.20625);
    delay(297.61875);
    EasyBuzzer.singleBeep( 1567, 89.285625);
    delay(99.20625);
    delay(297.61875);
    EasyBuzzer.singleBeep( 1975, 89.285625);
    delay(99.20625);
    delay(297.61875);
    EasyBuzzer.singleBeep( 1479, 89.285625);
    delay(99.20625);
    delay(297.61875);
    EasyBuzzer.singleBeep( 1046, 89.285625);
    delay(99.20625);
    delay(297.61875);
    EasyBuzzer.singleBeep( 1567, 89.285625);
    delay(99.20625);
    delay(297.61875);
    EasyBuzzer.stopBeep();
}

void ganar(){
  EasyBuzzer.singleBeep( 587, 63.2023125);
  delay(70.2247916667);
  EasyBuzzer.singleBeep( 440, 63.2023125);
  delay(70.2247916667);
  EasyBuzzer.singleBeep( 587, 63.2023125);
  delay(70.2247916667);
  EasyBuzzer.singleBeep( 739, 63.2023125);
  delay(70.2247916667);
  EasyBuzzer.singleBeep( 587, 63.2023125);
  delay(70.2247916667);
  EasyBuzzer.singleBeep( 739, 63.2023125);
  delay(70.2247916667);
  EasyBuzzer.singleBeep( 880, 63.2023125);
  delay(70.2247916667);
  EasyBuzzer.singleBeep( 440, 126.404625);
  delay(140.449583333);
  EasyBuzzer.singleBeep( 440, 126.404625);
  delay(140.449583333);
  EasyBuzzer.singleBeep( 369, 126.404625);
  delay(140.449583333);
  delay(140.449583333);
  EasyBuzzer.singleBeep( 391, 126.404625);
  delay(140.449583333);
  EasyBuzzer.singleBeep( 391, 126.404625);
  delay(140.449583333);
  EasyBuzzer.singleBeep( 329, 126.404625);
  delay(140.449583333);
  delay(140.449583333);
  EasyBuzzer.singleBeep( 293, 126.404625);
  delay(140.449583333);
  EasyBuzzer.singleBeep( 329, 126.404625);
  delay(140.449583333);
  EasyBuzzer.singleBeep( 293, 126.404625);
  delay(140.449583333);
  EasyBuzzer.singleBeep( 329, 126.404625);
  delay(140.449583333);
  EasyBuzzer.singleBeep( 293, 126.404625);
  delay(140.449583333);
  delay(140.449583333);
  EasyBuzzer.singleBeep( 293, 126.404625);
  delay(140.449583333);
  delay(140.449583333);
  EasyBuzzer.singleBeep( 440, 126.404625);
  delay(140.449583333);
  EasyBuzzer.singleBeep( 440, 126.404625);
  delay(140.449583333);
  EasyBuzzer.singleBeep( 369, 126.404625);
  delay(140.449583333);
  delay(140.449583333);
  EasyBuzzer.singleBeep( 391, 126.404625);
  delay(140.449583333);
  EasyBuzzer.singleBeep( 391, 126.404625);
  delay(140.449583333);
  EasyBuzzer.singleBeep( 329, 126.404625);
  delay(140.449583333);
  delay(140.449583333);
  EasyBuzzer.singleBeep( 293, 126.404625);
  delay(140.449583333);
  EasyBuzzer.singleBeep( 329, 126.404625);
  delay(140.449583333);
  EasyBuzzer.singleBeep( 293, 126.404625);
  delay(140.449583333);
  EasyBuzzer.singleBeep(277, 126.404625);
  delay(140.449583333);
  EasyBuzzer.singleBeep( 246, 63.2023125);
  delay(70.2247916667);
  delay(491.573541667);
  EasyBuzzer.singleBeep( 440, 126.404625);
  delay(140.449583333);
  EasyBuzzer.singleBeep( 440, 126.404625);
  delay(140.449583333);
  EasyBuzzer.singleBeep( 369, 126.404625);
  delay(140.449583333);
  delay(140.449583333);
  EasyBuzzer.singleBeep( 391, 126.404625);
  delay(140.449583333);
  EasyBuzzer.singleBeep( 391, 126.404625);
  delay(140.449583333);
  EasyBuzzer.singleBeep( 329, 126.404625);
  delay(140.449583333);
  delay(140.449583333);
  EasyBuzzer.singleBeep( 293, 126.404625);
  delay(140.449583333);
  EasyBuzzer.singleBeep( 329, 126.404625);
  delay(140.449583333);
  EasyBuzzer.singleBeep( 293, 126.404625);
  delay(140.449583333);
  EasyBuzzer.singleBeep( 329, 126.404625);
  delay(140.449583333);
}

void inicio(){
  EasyBuzzer.singleBeep(  195, 80.4570546875);
    delay(89.3967274306);
    delay(97.1703559028);
    EasyBuzzer.singleBeep(  146, 80.4570546875);
    delay(89.3967274306);
    delay(97.1703559028);
    EasyBuzzer.singleBeep(  195, 80.4570546875);
    delay(89.3967274306);
    delay(283.737439236);
    EasyBuzzer.singleBeep(  195, 80.4570546875);
    delay(89.3967274306);
    delay(470.304522569);
    EasyBuzzer.singleBeep(195, 80.4570546875);
    delay(89.3967274306);
    delay(3.88681423611);
    EasyBuzzer.singleBeep(  195, 80.4570546875);
    delay(89.3967274306);
    delay(3.88681423611);
    EasyBuzzer.singleBeep(  195, 80.4570546875);
    delay(89.3967274306);
    delay(283.737439236);
    EasyBuzzer.singleBeep(  195, 80.4570546875);
    delay(89.3967274306);
    delay(283.737439236);
    EasyBuzzer.singleBeep(  195, 80.4570546875);
    delay(89.3967274306);
    delay(283.737439236);
    EasyBuzzer.singleBeep(  174, 108.442117188);
    delay(120.491241319);
    delay(3.88681423611);
    EasyBuzzer.singleBeep(  174, 108.442117188);
    delay(120.491241319);
    delay(3.88681423611);
    EasyBuzzer.singleBeep(  174, 108.442117188);
    delay(120.491241319);
    delay(3.88681423611);
    EasyBuzzer.singleBeep(  174, 108.442117188);
    delay(120.491241319);
    delay(3.88681423611);
    EasyBuzzer.singleBeep(  174, 108.442117188);
    delay(120.491241319);
    delay(3.88681423611);
    EasyBuzzer.singleBeep(  220, 108.442117188);
    delay(120.491241319);
    delay(3.88681423611);
    EasyBuzzer.singleBeep(  195, 279.850625);
    delay(310.945138889);
    delay(62.1890277778);
    EasyBuzzer.singleBeep(  146, 164.412242188);
    delay(182.680269097);
    delay(3.88681423611);
    EasyBuzzer.singleBeep(  195, 279.850625);
    delay(310.945138889);
    delay(62.1890277778);
    EasyBuzzer.singleBeep(146, 164.412242188);
    delay(182.680269097);
    delay(3.88681423611);
    EasyBuzzer.singleBeep(  195, 164.412242188);
    delay(182.680269097);
    delay(3.88681423611);
    EasyBuzzer.singleBeep(  146, 164.412242188);
    delay(182.680269097);
    delay(3.88681423611);
    EasyBuzzer.singleBeep(  174, 279.850625);
    delay(310.945138889);
    delay(62.1890277778);
    EasyBuzzer.singleBeep(  130, 164.412242188);
    delay(182.680269097);
    delay(3.88681423611);
    EasyBuzzer.singleBeep(  174, 279.850625);
    delay(310.945138889);
    delay(62.1890277778);
    EasyBuzzer.singleBeep(  130, 164.412242188);
    delay(182.680269097);
    delay(3.88681423611);
    EasyBuzzer.singleBeep(  174, 164.412242188);
    delay(182.680269097);
    delay(3.88681423611);
    EasyBuzzer.singleBeep(  130, 164.412242188);
    delay(182.680269097);
    delay(3.88681423611);
}

void menu(){
    EasyBuzzer.singleBeep(  369, 62.6816484375);
    delay(69.6462760417);
    delay(75.7024739583);
    EasyBuzzer.singleBeep(  493, 62.6816484375);
    delay(69.6462760417);
    delay(75.7024739583);
    EasyBuzzer.singleBeep(  554, 62.6816484375);
    delay(69.6462760417);
    delay(75.7024739583);
    EasyBuzzer.singleBeep(  493, 62.6816484375);
    delay(69.6462760417);
    delay(366.399973958);
    EasyBuzzer.singleBeep( 659, 218.023125);
    delay(242.247916667);
    delay(484.495833333);
    EasyBuzzer.singleBeep(  493, 62.6816484375);
    delay(69.6462760417);
    delay(366.399973958);
    EasyBuzzer.singleBeep(  659, 218.023125);
    delay(242.247916667);
    delay(48.4495833333);
    EasyBuzzer.singleBeep(  369, 62.6816484375);
    delay(69.6462760417);
    delay(75.7024739583);
    EasyBuzzer.singleBeep(  493, 62.6816484375);
    delay(69.6462760417);
    delay(75.7024739583);
    EasyBuzzer.singleBeep(  554, 62.6816484375);
    delay(69.6462760417);
    delay(75.7024739583);
    EasyBuzzer.singleBeep(  369, 62.6816484375);
    delay(69.6462760417);
    delay(75.7024739583);
    EasyBuzzer.singleBeep(  369, 62.6816484375);
    delay(69.6462760417);
    delay(75.7024739583);
    EasyBuzzer.singleBeep(  493, 62.6816484375);
    delay(69.6462760417);
    delay(75.7024739583);
    EasyBuzzer.singleBeep(  369, 62.6816484375);
    delay(69.6462760417);
    delay(75.7024739583);
    EasyBuzzer.singleBeep( 493, 62.6816484375);
    delay(69.6462760417);
    delay(75.7024739583);
    EasyBuzzer.singleBeep(  369, 62.6816484375);
    delay(69.6462760417);
    delay(75.7024739583);
    EasyBuzzer.singleBeep(  493, 62.6816484375);
    delay(69.6462760417);
    delay(75.7024739583);
    EasyBuzzer.singleBeep(  369, 62.6816484375);
    delay(69.6462760417);
    delay(75.7024739583);
    EasyBuzzer.singleBeep(  493, 62.6816484375);
    delay(69.6462760417);
    delay(75.7024739583);
    EasyBuzzer.singleBeep(  369, 62.6816484375);
    delay(69.6462760417);
    delay(75.7024739583);
    EasyBuzzer.singleBeep(  493, 62.6816484375);
    delay(69.6462760417);
    delay(75.7024739583);
    EasyBuzzer.singleBeep(  369, 62.6816484375);
    delay(69.6462760417);
    delay(75.7024739583);
    EasyBuzzer.singleBeep(  493, 62.6816484375);
    delay(69.6462760417);
    delay(75.7024739583);
    EasyBuzzer.singleBeep(  369, 62.6816484375);
    delay(69.6462760417);
    delay(75.7024739583);
    EasyBuzzer.singleBeep(  493, 62.6816484375);
    delay(69.6462760417);
    delay(75.7024739583);
    EasyBuzzer.singleBeep( 369, 62.6816484375);
    delay(69.6462760417);
    delay(75.7024739583);
}

void batalla(){
  EasyBuzzer.singleBeep(880, 1048);
  delay(116);
  EasyBuzzer.singleBeep(830, 10485);
  delay(116);
  EasyBuzzer.singleBeep( 783, 10485);
  delay(116);
  EasyBuzzer.singleBeep( 739, 10485);
  delay(116);
  EasyBuzzer.singleBeep( 880, 10485);
  delay(116);
  EasyBuzzer.singleBeep(783, 10485);
  delay(116);
  EasyBuzzer.singleBeep(739, 10485);
  delay(116);
  EasyBuzzer.singleBeep(698, 10485);
  delay(116);
  EasyBuzzer.singleBeep( 880, 10485);
  delay(116);
  EasyBuzzer.singleBeep( 739, 10485);
  delay(116);
  EasyBuzzer.singleBeep( 698, 10485);
  delay(116);
  EasyBuzzer.singleBeep( 659, 10485);
  delay(116);
  EasyBuzzer.singleBeep( 880, 10485);
  delay(116);
  EasyBuzzer.singleBeep( 698, 10485);
  delay(116);
  EasyBuzzer.singleBeep( 659, 10485);
  delay(116);
  EasyBuzzer.singleBeep( 622, 10485);
  delay(116);
  EasyBuzzer.singleBeep( 880, 10485);
  delay(116);
  EasyBuzzer.singleBeep( 659, 10485);
  delay(116);
  EasyBuzzer.singleBeep( 622, 10485);
  delay(116);
  EasyBuzzer.singleBeep( 587, 10485);
  delay(116);
  EasyBuzzer.singleBeep( 880, 10485);
  delay(116);
  EasyBuzzer.singleBeep( 622, 10485);
  delay(116);
  EasyBuzzer.singleBeep( 587, 10485);
  delay(116);
  EasyBuzzer.singleBeep( 554, 10485);
  delay(116);
  EasyBuzzer.singleBeep( 880, 10485);
  delay(116);
  EasyBuzzer.singleBeep( 587, 10485);
  delay(116);
  EasyBuzzer.singleBeep( 554, 10485);
  delay(116);
  EasyBuzzer.singleBeep( 523, 10485);
  delay(116);

  EasyBuzzer.singleBeep( 880, 10485);
  delay(116);
  EasyBuzzer.singleBeep( 554, 10485);
  delay(116);
  EasyBuzzer.singleBeep( 523, 10485);
  delay(116);
  EasyBuzzer.singleBeep(493, 10485);
  delay(116);
  EasyBuzzer.singleBeep( 987, 10485);
  delay(116);
  delay(361);
  EasyBuzzer.singleBeep( 987, 10485);
  delay(116);
  delay(314);
  EasyBuzzer.singleBeep(880, 10485);
  delay(116);
  delay(780);
  EasyBuzzer.singleBeep( 493, 62914);
  delay(699);
  EasyBuzzer.singleBeep( 369, 10485);
  delay(116);
  delay(466);
  EasyBuzzer.singleBeep( 493, 41943);
  delay(466);
  EasyBuzzer.singleBeep( 369, 41943);
  delay(466);
  EasyBuzzer.singleBeep( 493, 41943);
  delay(466);
  EasyBuzzer.singleBeep( 523, 83886);
  delay(932);
  EasyBuzzer.singleBeep(493, 62914);
  delay(699);
  EasyBuzzer.singleBeep( 369, 10485);
  delay(116);
  delay(466);
  EasyBuzzer.singleBeep( 493, 41943);
  delay(466);
  EasyBuzzer.singleBeep( 369, 41943);
  delay(466);
  EasyBuzzer.singleBeep(493, 41943);
  delay(466);
  EasyBuzzer.singleBeep( 440, 33554);
  delay(372);
  EasyBuzzer.singleBeep( 391, 16777);
  delay(186);
  EasyBuzzer.singleBeep( 587, 83886);
  delay(932);
  EasyBuzzer.singleBeep( 391, 83886);
  delay(932);
  EasyBuzzer.singleBeep( 440, 33554);
  delay(372);
  EasyBuzzer.singleBeep( 391, 16777);
  delay(186);
  EasyBuzzer.singleBeep( 659, 83886);
  delay(932);
}
