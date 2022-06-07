# tcc_codigos
Códigos de Arduino utilizados no TCC
Dentre os arquivos existentes tem-se:
1. load_cell_analog_read.ino - primeira simulação: foi utilizado um amp-op na saída da ponte de wheatstone da célula de carga, e a saída do amp-op foi lida pela porta analógica do Arduino;
2. load_cell_hx711.ino - segunda simulação: foi utilizado o módulo conversor AD HX711 e o valor da célula de carga foi então convertido e lido nas portas digitais do Arduino;
3. sensor_indutivo_ddt.ino - terceira simulação: foi utilizado um divisor de tensão para possibilitar a comunicação entre o sensor indutivo e o Arduino;
4. sendor_indutivo_2.ino - quarta simulação: foi utilizado a configuração pull up e um tbj/foto-acoplador para possibilitar a comunicação entre o sensor indutivo e o Arduino;
5. Integracao_de_sensores.ino - quinta simulação: foi realizado a integração dos sensores nas topologias que apresentaram os melhores resultados (com módulo HX711 e divisor de tensão;
6. HX711_ADC-1.2.12.zip - Biblioteca do módulo HX711 utilizada;
7. valida_cpf_esp01_serial.ino - simulação do sistema de comunicação: código utilizado no Arduino UNO para validar o CPF, e caso válido, enviar a String do CPF via comunicação serial para o esp8266-01;
8. fire_base_esp01.ino - simulação do sistema de comunicação: código utilizado no esp8266-01 para ler a serial e executar a comunicação com o banco de dados Firebase via WiFi;
9. leitura_pos_calibracao.ino - simulação final: após realizar a calibração, esse código realiza a simulação geral do sistema, incluindo célula de carga, módulo HX711, sensor de presença indutivo, esp8266-01.
