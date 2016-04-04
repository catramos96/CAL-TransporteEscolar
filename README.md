# Comandos do git #

## 1- Clonar o repositório para o computador: ##

* clicar no botão à esquerda chamado 'clone'

* clicar 'clone in source tree'

* seguir as instruções

## 2- Para fazer commits: ##

## A partir do eclipse (provavelmente vou começar a usar este)

* botão direito em cima do projeto

* 'team'

* 'commit' -> escreves as cenas

* 'team' e 'push'

## A partir do source tree ##

o source tree tem todos os botões: push, pull, commit... basta clicar e aparece a janela com o que é preciso fazer. 
No git devemos sempre seguir a ordem : pull (ver se já existem coisas no repositório), commit (mensagem com o que fizeste) , push (coloca no repositório).

## A partir do terminal do source tree (mais fiável?) ##

* clicar onde diz 'terminal'

### Sempre que se abre o terminal é preciso fazer login ###

* git config --global user.name "Vosso nome"

* git config --global user.email "Vosso email da conta do bb"

### Para fazer commits estes passos têm de ser seguidos. Todos e por esta ordem para evitar problemas ###

* git add -A    //Adiciona todos os ficheiros novos ou alterados ao commit

* git commit -a -m "Mensagem do commit"

* git pull      //Ir buscar qualquer atualização ao rep antes de fazer upload das 
vossas adiçõees de código

* git push     //Faz upload do commit para o repositório


## Outros comandos ##

* git status   //diz se o vosso rep está atualizado com o do site