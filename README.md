# pa_DFS_BFS

Detalhes de implementação e escolhas de projeto:
Primeiramente, recebe-se os dados (quantidade de linhas e colunas) para depois poder alocar os espaços de memória. A única biblioteca utilizada foi a de fila dinâmica, para a execução do algoritmo da BFS.
A criação do labirinto foi feita com mais duas linhas e mais duas colunas, para que se pudesse criar uma "parede" de '#', assim, na hora da checagem dos vizinhos, não existe o risco de haver algum ponto como lixo de memória.
Cria-se também uma matriz enumerada que serve de auxiliar para a implementação da lista de adjacências: para cada vértice da matriz (cada espaço no labirinto) são checados seus 4 vizinhos (esq, dir, acima, abaixo) e, se para cada checagem, o vizinho for um ponto '.', insere o número (conforme a matriz enumerada) na lista de adjacências.
Após estes passos, a função DFS é executada, preenchendo seu vetor de pais. Através desse vetor, percorre-se (do fim para o começo) o labirinto com 'x', marcando o caminho. A função que preenche o labirinto utiliza o seguinte cálculo: a linha a ser marcada com um 'x' será o resultado da divisão inteira da última posição do labirinto pelo número de colunas. A coluna segue o mesmo cálculo, porém, ao invés da divisão, calcula-se o resto. Este cálculo é feito percorrendo o vetor de pais, até que este valor chegue na primeira posição (0).
Se no caminho algum pai for igual a -1, significa que não há como seguir pelo labirinto, imprimindo uma mensagem e encerrando o programa.
Após, se o caminho foi percorrido, são impressas as saídas e o algoritmo da BFS se inicia (depois de "limpar" o caminho feito pela DFS). Os passos para a BFS são os mesmos que os da BFS. Como somente seus vetores de pais são utilizados, as funções são as mesmas para recebe-los.
No fim, toda a memória é desalocada e o programa retorna 0.
