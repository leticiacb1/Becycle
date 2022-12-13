Shell Sort
======
O problema
------------------------------------------------
Imagine que você tenha que ordenar em ordem não decrescente o seguinte vetor:

![](exemplo.drawio.png)

Dentre os algoritimos de ordenação que você aprendeu ao longo da disciplina, suponhamos que sua escolha para realizar essa tarefa foi o Insertion Sort. 

Insertion Sort
------------------------------------------------
Para falar do Shell Sort, precisamos antes relembrar o funcionamento do Insertion Sort, que deu origem a ele. 
A ideia do Insertion Sort é inspirada no que você faz quando está ordenando uma mão de cartas de baralho: você tem uma “parte ordenada” que começa vazia e vai aumentando conforme você “insere” novas cartas nela. A chave é que, quando você faz essa “inserção”, você a faz no lugar certo, para não estragar a ordenação. Considere o exemplo abaixo.

![](cards.png)

Nesse exemplo, a mão tem a “parte ordenada” `md {2, 4, 5, 10}` e quer “inserir” a carta `md 7`. Para não estragar a ordenação, essa “inserção” é feita entre `md 5` e `md 10`.

O código (que você já conhece)
----------------
```c
void insertion_sort(int v[], int n) {
    for (int i = 1; i < n; i++) {
        int temp = v[i];

        int j = i;
        while (j > 0 && v[j - 1] > temp) {
            v[j] = v[j - 1];
            j--;
        }

        v[j] = temp;
    }
}
```
Veja a animação abaixo. Os elementos vermelhos representam a “parte ordenada que vai ficando cada vez maior”.

:insertion

??? Checkpoint

Observe a animação a partir da imagem 60. Quantos deslocamentos são necessários para colocar o elemento `md 1` na posição correta?

::: Gabarito
São necessários 8 deslocamentos até que o elemento `md  1` esteja em sua posição correta. Muitos, não?
:::

???

Tanto deslocamento...
---------

Que o Insertion Sort é ótimo método de ordenação, isso todo mundo sabe. Entretanto, para vetores onde o número menor está em posições mais distantes, como no exemplo acima, acaba ocorrendo muitos deslocamentos para poder mover o número menor para sua posição correta, já que a ordenação por inserção só troca itens que estão lado a lado de cada vez. 

E se tivesse um modo de verificar e comparar os elementos em posições mais distantes com as de meio e começo de vetor? Ou melhor ainda, de já ir ordenando esses números para as posições mais próximas de suas posições de ordenação? Para a nossa sorte, existe alguém que já pensou e projetou esse algorítmo.

Algorítmo Shell Sort
---------

Em 1959, Donald Shell observou essa "falha" no algoritmo do Insertion Sort, e com isso, pensou numa solução. O Shell Sort é, nada mais nada menos, do que um refinamento do Insertion Sort para vetores maiores. A ideia consiste em dois pontos principais:

* Definir um gap (intervalo) para a criação de sub-vetores (h);

* Ordenação dos sub-vetores;

Na criação do método, Donald definiu o intervalo da seguinte maneira: 

$$ h = \frac{n}{2}$$, onde n é o tamanho do vetor e h é um número inteiro.

Portanto, o método consiste em separar o vetor original a ser ordenado em vários sub-vetores, considerando um intervalo específico entre os elementos da lista, e para cada sub-vetor, irá ser feito o método do insertion para fazer as trocas entre os elementos, de forma de que se obtém o vetor original atualizado.

??? Checkpoint

Pensando no exemplo anterior apresentado no Insertion Sort, como ficariam os sub-vetores utilizando o intervalo que Donald Shell definiu?

::: Gabarito
Como se tem um vetor de tamanho 10, o intervalo seria de 5 em 5, de forma que:

![](exemplo_subvetores.png)

:::

???

??? Checkpoint

E como ficaria os sub-vetores ordenados por Insertion Sort e o vetor original após essas ordenações?

::: Gabarito
Vendo cada sub-vetor e fazendo sua ordenação por insertion, têm-se que:

![](exemplo_insertion_subvetor1.png)

Tendo feitas essas ordenações, o vetor original fica da seguinte maneira:

![](exemplo_primeiro_loop.png)

(Só nessa primeira passagem, você consegue perceber que o 1, segundo menor número do vetor, passou da posição 9 já para a posição 4? Ao invés de ele fazer 5 deslocamentos pelo método do Insertion para chegar nessa posição, pelo Shell Sort, ele fez somente um deslocamento.)
:::

???

Entretanto, fazendo isso apenas uma vez não me confirma que o vetor está realmente ordenado. E isso faz sentido, já que é feita a comparação apenas entre vetores que estão a um intervalo h um do outro, e não comparando todos os elementos como deveria ser. 

É por isso que isso representa apenas a primeira passagem do algorítmo e a ideia principal de Donald Shell, que é ficar dividindo esse intervalo por 2, percorrer o vetor e ordenar os sub-vetores a cada passagem, até chegar no gap = 1, que é nada mais, nada menos do que o próprio Insertion Sort, e que também me confirma que o vetor está totalmente ordenado como deveria ser.

!!! Aviso
Lembre-se que o intervalo (h) tem que ser um número inteiro!! Considerando também a linguagem C, o inteiro retornado pela divisão tende ao valor mais próximo de 0.
!!!


??? Checkpoint

Agora, como ficaria os sub-vetores e o vetor original após a segunda passagem do Shell Sort?

::: Gabarito
Como h = 2 e sendo feito os mesmos passos anteriores, têm-se o seguinte resultado:

![](exemplo_segundo_loop.png)

(Agora, o 1 está no índice 0, e até agora fez somente 3 deslocamentos, sendo 1 do Insertion Sort no sub-vetor 5 e 2 do Insertion Sort feito no sub-vetor 6. Além disso, metade do vetor já se encontra praticamento ordenado.)
:::

???

??? Checkpoint

Finalmente, agora na terceira passagem do Shell Sort, se tem h = 1, ou seja, agora é aplicado o Insertion Sort pela última vez. E aí? Como fica o vetor final?

::: Gabarito

![](exemplo_ordenado.png)

(Percebe-se que, no geral, o 1 se deslocou apenas 4 vezes ao invés de ter 8 deslocamentos, assim como o 9, que antes tinha 9 deslocamentos, agora fez apenas 3 deslocamentos. Ou seja, o Shell Sort faz uma diferença absurda quando os elementos estão distantes da sua posição ordenada!)
:::

???

Tendo pensado e refletido sobre toda essa teoria, agora fica mais fácil de se entender o código por trás, considerando a linguagem C:

```c
void shell_sort(int v[], int n) {
     // Incremento original de Donald Shell, intervalos em N/2, N/4, N/8 ... 
  for (int h = n / 2; h > 0; h /= 2) {
    for (int i = h; i < n; i += 1) {
      int temp = array[i];
      int j;
      for (j = i; j >= h && array[j - h] > temp; j -= h) {
        array[j] = array[j - h];
      }
      array[j] = temp;
    }
  }
}
```
Entretanto, e se fosse um vetor de tamanho 9? ou de tamanho 15? Será se a melhor eficiência seria dividindo por dois? Será se não seria melhor dividir por 3? Ou cinco no caso de tamanho 15?

Essa é a grande questão do algorítmo de Shell Sort, ele permite você escolher o tanto de incremento que quer ter, de forma que se tenha a melhor complexidade
e eficiência possível. 

Complexidade e Eficiência
---------

!!! Aviso
Para os exercícios abaixo, utiliza-se apenas o incremento de Donald Shell.
!!!

Exercícios
---------
??? Questão 1

Ordene o seguinte vetor utilizando o Shell Sort:

![](q1_vetor.png)

::: Gabarito

![](q1-gabarito.png)

:::

???

??? Questão 2

Ordene o seguinte vetor utilizando o Shell Sort:

![](q2-vetor.png)

::: Gabarito

![](q2-gabarito.png)

Lembre-se que na divisão em C, o valor vai para o que é mais próximo de zero, por isso, quando o tamanho do vetor é 7, ele tem apenas o gap de 3 e 1, e não de 4, 2 e 1.
:::

???

Para criar um parágrafo, basta escrever um texto contínuo, sem pular linhas.

Você também pode criar

1. listas;

2. ordenadas,

assim como

* listas;

* não-ordenadas

e imagens. Lembre que todas as imagens devem estar em uma subpasta *img*.

![](logo.png)

Para tabelas, usa-se a [notação do
MultiMarkdown](https://fletcher.github.io/MultiMarkdown-6/syntax/tables.html),
que é muito flexível. Vale a pena abrir esse link para saber todas as
possibilidades.

| coluna a | coluna b |
|----------|----------|
| 1        | 2        |

Ao longo de um texto, você pode usar *itálico*, **negrito**, {red}(vermelho) e
[[tecla]]. Também pode usar uma equação LaTeX: $f(n) \leq g(n)$. Se for muito
grande, você pode isolá-la em um parágrafo.

$$\lim_{n \rightarrow \infty} \frac{f(n)}{g(n)} \leq 1$$

Para inserir uma animação, use `md :` seguido do nome de uma pasta onde as
imagens estão. Essa pasta também deve estar em *img*.

:bubble

Você também pode inserir código, inclusive especificando a linguagem.

``` py
def f():
    print('hello world')
```

``` c
void f() {
    printf("hello world\n");
}
```

Se não especificar nenhuma, o código fica com colorização de terminal.

```
hello world
```


!!! Aviso
Este é um exemplo de aviso, entre `md !!!`.
!!!


??? Exercício

Este é um exemplo de exercício, entre `md ???`.

::: Gabarito
Este é um exemplo de gabarito, entre `md :::`.
:::

???
