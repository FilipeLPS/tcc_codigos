# tcc_codigos
Códigos de Arduino utilizados no TCC
Dentre os arquivos existentes tem-se:
1. load_cell_analog_read.ino - primeira simulação: foi utilizado um amp-op na saída da ponte de wheatstone da célula de carga, e a saída do amp-op foi lida pela porta analógica do Arduino;
2. load_cell_hx711.ino - segunda simulação: foi utilizado o módulo conversor AD HX711 e o valor da célula de carga foi então convertido e lido nas portas digitais do Arduino;
3. sensor_indutivo_ddt.ino - terceira simulação: foi utilizado um divisor de tensão para possibilitar a comunicação entre o sensor indutivo e o Arduino;
4. Integracao_de_sensores.ino - quarta simulação: foi realizado a integração dos sensores nas topologias que apresentaram os melhores resultados (com módulo HX711 e divisor de tensão;
