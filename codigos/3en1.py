# encoding: utf-8

#la lógica principal (y compartida por los tres algoritmos) 
#se encuentra en la función "main" abajo del todo.

#lo que se obtiene es un conjunto de pares de indices que marcan
#el comienzo y el final de las ventanas no nulas. Se entiende
#por tanto los indices no incluidos en los intervalos de dichos
#pares serán siempre nulos -compuestos exclusivamente por 0s-

#Ejecución de ejemplo:
#
# Message array: [1,1,0,1,1,0,0,0,0,0,1,0,1,1,0,0]
# b: 3
# It's missing the algorithm processBlockAlg2
# (0, 2) -> [1, 1, 0]
# (3, 5) -> [1, 1, 0]
# (6, 8) -> [0, 0, 0]
# (8, 10) -> [0, 0, 1]
# (11, 13) -> [0, 1, 1]
# (14, 15) -> [0, 0]
# 
# 
# Results for algorithm processBlockAlg3
# (0, 2) -> [1, 1, 0]
# (3, 5) -> [1, 1, 0]
# (10, 12) -> [1, 0, 1]
# (13, 15) -> [1, 0, 0]
# 
# 
# Results for algorithm processBlockAlg4
# (0, 1) -> [1, 1]
# (3, 4) -> [1, 1]
# (10, 12) -> [1, 0, 1]
# (13, 13) -> [1]
# 
# 
# Results for algorithm processBlockAlg5
# (0, 1) -> [1, 1]
# (3, 4) -> [1, 1]
# (10, 10) -> [1]
# (12, 13) -> [1, 1]
#




def processBlockAlg3(block):
  #nada que hacer realmente. Los subbloques son siempre
  #de longitud constante
  return len(block)-1


def processBlockAlg4(block):
  #se busca el primer no nulo empezando por la izq.
  #siempre habra alguno: en el peor caso, el que 
  #motivo la llamada a esta funcion, el primero.

  #se devuelve la posicion relativa al bloque del no nulo
  #que completa la ventana
  lenBlock = len(block)
  for i in xrange(lenBlock):
    if block[-i-1] == 1:
      return lenBlock-i-1


def processBlockAlg5(block):
  #se busca el primer nulo empezando por la derecha.

  #se devuelve la posicion relativa al bloque del nulo
  #que completa la ventana, si existe
  lenBlock = len(block)
  for i in xrange(lenBlock):
    if block[i] == 0:
      return i-1
  else:
    return lenBlock-1



def printWindows(windows, message):
  for w in windows:
    print w, "->", message[w[0]:w[1]+1]



def main():
  message = input("Message array: ") #en la forma [1,0,0,1.... ] ie, valores binarios separados
                                     #por comas y entre [ ]
  b = input("b: ")

  for algInTurn in (processBlockAlg3, processBlockAlg4, processBlockAlg5):
    windows = []; i = 0
    while i < len(message):  #mientras haya simbolos en el mensaje...
      if message[i] == 1:
        #empieza la ventana. hasta donde llega?
        j = algInTurn( message[i:i+b] ) #para el alg en cuestion, ver hasta donde
                                        #llega la ventana que comienza en el índice "i"
        windows.append( (i,j+i) ) #se adjunta la ventana 
        i += j+1 #y se mueve "el cursor" al siguiente simbolo aún no considerado
      else: # digito i-esimo del mensaje == 0, saltar
        i += 1

    print "Results for algorithm", algInTurn.__name__
    printWindows(windows,message)
    print "\n"


if __name__ == "__main__":
  main()


