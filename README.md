🛑 Sistema de Registro de Catástrofes Naturais
Este programa em C permite cadastrar relatos de catástrofes naturais com informações geográficas e pessoais, realizar consultas baseadas em localização e gravidade, além de salvar os registros em arquivo para posterior análise.

📋 Funcionalidades
Cadastro de relatos com:
  1. Tipo de catástrofe (ex: enchente, deslizamento)
  2. Região
  3. CPF do usuário (validação de 11 dígitos)
  4. Data no formato DD/MM/AAAA
  5. Nível de gravidade (1 a 5)
  6. Localização (latitude e longitude)
  7. Listagem de todos os relatos cadastrados
  8. Filtro por distância: exibe apenas relatos a até 10 km de uma localização informada
  9. Salvamento automático em arquivo .txt ao sair do programa

📌 Menu Principal
Ao rodar o programa, será exibido o seguinte menu:
1 - Cadastro
2 - Lista de Cadastros
3 - Filtrar por Distancia
4 - Sair

🧠 Exemplos de Uso
✅ Cadastrando um Relato
Qual catastrofe: enchente
Qual regiao: zona_norte
Digite seu CPF (apenas numeros, 11 digitos): 12345678901
Qual data (DD/MM/AAAA): 01/06/2025
Digite a gravidade(de 1 a 5):...3
Digite a latitude: -23.5505
Digite a longitude: -46.6333

✅ Listando Relatos
Selecionar a opção 2 mostrará:
====Lista de Cadastros====

Tipo:...enchente
Regiao:...zona_norte
Cpf:...12345678901
Data:...01/06/2025
Gravidade:...3
Localizacao: (-23.5505, -46.6333)
===========================

✅ Filtrar por Distância
Digite sua latitude: -23.5500
Digite sua longitude: -46.6300

Relatos em ate 10km:
...

💾 Arquivo de Saída
Ao sair do programa, os relatos são salvos no arquivo relatos.txt no seguinte formato:
enchente;zona_norte;12345678901;01/06/2025;3
Obs: Apenas os dados principais são salvos no arquivo (localização não incluída)

✅Integrantes:
Miguel Vanucci Delgado RM: 563491
Igor Zuvela Villaça Felicio RM: 563602
