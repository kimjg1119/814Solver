## Class : Gene

유전자를 표현하는 컨테이너 클래스입니다.

### Variables

| 접근제어자 | 이름 | 설명                                                         |
| ---------- | ---- | ------------------------------------------------------------ |
| private    | gene | 8*14 이차원 배열로 0부터 9까지의 원소를 가지는 유전자입니다. |

### Constructor

| 이름                    | 설명                                                     |
| ----------------------- | -------------------------------------------------------- |
| Gene(void)              | 모든 원소는 0으로 초기화됩니다.                          |
| Gene(RandomManager& rm) | 모든 원소는 0부터 9 사이 난수로 초기화됩니다.            |
| Gene(String &gene)      | 1차원 문자열을 입력으로 받아, 2차원 배열로 변환해줍니다. |

### Functions

| 접근제어자 | 이름                                 | 설명                                                         |
| ---------- | ------------------------------------ | ------------------------------------------------------------ |
| pubic      | void GetGene(int[8][14] arr)         | 이차원 배열을 입력으로 받아, 그 배열에 현재 유전자를 넣어줍니다. |
| public     | int GetGene(int i, int j)            | (i, j)에 위치한 원소를 반환합니다.                           |
| public     | void InitGene(int[8][14] arr)        | 이차원 배열을 입력으로 받아, 그 배열로 유전자를 초기화합니다. |
| public     | void ModifyGene(int i, int j, int k) | (i, j)에 위치한 원소를 k로 변경합니다. 돌연변이 작업을 수행할 때 주로 사용합니다. |



## EvalManager

### Variables

| 접근제어자 | 이름             | 설명                                               |
| ---------- | ---------------- | -------------------------------------------------- |
| private    | int dx[8], dy[8] | none                                               |
| private    | int ignore_limit | EvalIgnoreOne에서 고려할 숫자의 상한을 설정합니다. |

### Functions

| 접근제어자 | 이름                                                         | 설명                                                         |
| ---------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| private    | bool BackTracking(const int v[8][14], int i, int j, int now) | 이차원배열 v에서 now를 찾는 백트래킹을 수행합니다.           |
| private    | bool HasNum(const int v[8][14], int now)                     | 이차원배열 v에 now가 존재하는지 확인합니다.<br />BackTracking을 수행합니다. |
| private    | int GetScore(const int v[8][14])                             | 이 유전자의 점수를 반환합니다.<br />HasNum을 수행합니다.     |
| private    | double GetScoreIgnoreOne(const int v[8][14])                 | 이 유전자의 점수를 반환합니다.<br />1부터 ignore_limit까지 보면서 존재하지 않는 수가 나올 때마다 점수의 증가 폭이 1/2로 감소합니다.<br />HasNum을 수행합니다. |
| public     | EvalIgnoreOne(Gene& g)                                       | return GetScoreIgnoreOne(~)                                  |
| public     | EvalScore(Gene& g)                                           | return getScore(~)                                           |





## GeneManager

유전자에 대한 간단한 연산을 수행할 수 있는 매니저 클래스입니다.

### Variables

| 접근제어자 | 이름             | 설명                                                         |
| ---------- | ---------------- | ------------------------------------------------------------ |
| private    | int dx[8], dy[8] | none                                                         |
| private    | RandomManager rm | 각종 랜덤 작업을 수행할 때 사용하는 RandomManager 객체입니다. |
| private    | Eval eval        | 점수 계산을 위해 사용하는 EvalManager 객체입니다.            |

### Constructor

| 이름                  | 설명                    |
| --------------------- | ----------------------- |
| GeneManager(int seed) | rm의 seed를 설정합니다. |

### Functions

| 접근제어자 | 이름                                                        | 설명                                                         |
| ---------- | ----------------------------------------------------------- | ------------------------------------------------------------ |
| private    | vector&lt;int&gt; BasicEvaluate(Gene& gene)                 | 이 유전자에서 만들 수 있는 10000 미만의 숫자에 대한 벡터를 반환합니다.<br />만들 수 있으면 1, 만들 수 없으면 0이 들어있습니다. 현재는 사용하지 않습니다. |
| public     | int EvaluateMax(Gene& gene)                                 | 이 유전자의 점수를 반환합니다.                               |
| public     | double EvaluateIgnoreOne(Gene& gene)                        | 이 유전자의 점수를 반환합니다.<br />이때 점수는 EvalManager::ignore_limit 까지의 숫자를 모두 보면서, 만들 수 없는 숫자가 나올 때마다 절반으로 감소합니다. |
| public     | void ProbMutate(Gene& gene, double prob, RandomManager &rm) | 유전자, 확률, RandomManager 객체를 받아 유전자의 각 원소에 대해 주어진 확률로 돌연변이를 수행합니다.<br />돌연변이의 결과로 바뀌는 값은 0~9 사이의 등확률 난수입니다. |
| public     | void Optimizer(Gene& gene, int max_iter)                    | 이 유전자에 대해 지역 최적화를 최대 max_iter번 수행합니다.   |
| public     | void Shuffle(Gene&)                                         | 이 유전자를 섞어줍니다.<br />주로 Local Optimal에서 탈출하기 위해 사용합니다. |



## RandomManager

난수에 대한 기본적인 연산을 수행할 수 있는 매니저 클래스입니다.

### Variables

| 접근제어자 | 이름                                                | 설명                                                         |
| ---------- | --------------------------------------------------- | ------------------------------------------------------------ |
| private    | mt19937_64 seed                                     | none                                                         |
| private    | uniform_int_distribution&lt;int&gt; rngInt09        | 미리 범위가 지정된 변수로, 0부터 9까지의 정수를 반환하기 위함입니다. 주로 유전자에 쓰입니다. |
| private    | uniform_real_distribution&lt;double&gt; rngDouble01 | 미리 범위가 지정된 변수로, 0부터 1까지의 실수를 반환하기 위함입니다. 주로 확률 관련 난수에 쓰입니다. |

### Constructor

| 이름                              | 설명               |
| --------------------------------- | ------------------ |
| RandomManager(unsigned int seed); | seed를 설정합니다. |

### Functions

| 접근제어자 | 이름                               | 설명                                      |
| ---------- | ---------------------------------- | ----------------------------------------- |
| public     | int RandomInt09(void)              | 0~9 사이의 정수를 반환합니다.             |
| public     | double RandomDouble01(void)        | 0~1 사이의 실수를 반환합니다.             |
| public     | double RandomDouble(double d)      | 0~d 사이의 실수를 반환합니다.             |
| public     | Pos RandomPosition(void)           | 무작위 좌표를 하나 반환합니다.            |
| public     | pair<Pos, Pos> TwoRandomPosition() | 겹치지 않는 무작위 좌표 2개를 반환합니다. |



## GeneAlgoManager

### Variables

| 접근제어자 | 이름                             | 설명                                                         |
| ---------- | -------------------------------- | ------------------------------------------------------------ |
| private    | double fitness_k                 | 룰렛 휠에서의 선택압을 조절합니다. 보다 구체적으로, 모든 유전자에 대해서 각 유전자가 가지는 확률 파이는 가장 좋은 유전자가 가장 나쁜 유전자의 fitness_k배가 됩니다. 나머지 유전자에 대해서는 그 사이에서 얻은 점수에 대해 선형입니다. 증가시킬수록 선택압이 증가합니다. 3~4가 주로 사용됩니다. |
| private    | double mutate_prob               | 각 원소에 대한 돌연변이 확률입니다. 증가시킬수록 선택압이 감소합니다. 0부터 1 사이입니다. |
| private    | double gene_mutate_prob          | 각 유전자에 대한 돌연변이 확률입니다. 이 확률을 만족시켜야 각 유전자의 각 원소에 대해서 돌연변이가 진행됩니다. 증가시킬수록 선택압이 감소합니다. 0부터 1 사이입니다. |
| private    | double all_init                  | 유전자에 대한 전체 초기화 확률입니다. 현재까지는 큰 의미가 없으며, 유전적 다양성을 늘려줄 수 있다는 기대 하에 이용하는 변수입니다. 0부터 1 사이입니다. |
| private    | int elite                        | 수정되거나 제거될 수 있는 변수입니다. 이제까지 등장한 유전자 중 가장 좋은 유전자를 이 변수의 값 만큼 유전자 풀에 추가합니다. 증가할수록 유전적 다양성이 줄어들고 안정성이 늘어납니다. 이 변수의 적절한 활용은 유전적 안정성이 깨지지 않게 하고 점수를 상승시키는 데 큰 기여를 하지만, 동시에 Local Maxima에 빠질 확률 또한 크게 증가시킵니다. |
| private    | int remain                       | 수정되거나 제거될 수 있는 변수입니다. remain에서 elite를 뺀 수 만큼 부모 개체를 그대로 유지시킵니다. 증가할수록 유전적 다양성이 줄어들고 안정성이 늘어납니다. |
| private    | int max_iter                     | Optimizer의 수행 횟수를 제한합니다.<br />값이 클수록 지역 최적화를 많이 수행하지만 속도 저하의 위험이 있습니다. |
| private    | int n                            | 유전자의 개수입니다.                                         |
| private    | double fitSum                    | 적합도의 합입니다. SelectParent 함수에서 사용됩니다.         |
| private    | Gene bestGene                    | 현재까지 등장한 것 중 가장 나은 유전자입니다.                |
| private    | vector&lt;Gene&gt; geneArr       | 유전자들을 담고 있는 벡터입니다.                             |
| private    | vector&lt;int&gt; geneScore      | 유전자들에 대한 점수를 담는 벡터입니다. 이는 문제에서 요구하는 값과 정확히 일치합니다. |
| private    | vector&lt;int&gt; geneFitScore   | 유전자들에 대한 평가 함수 점수를 담는 벡터입니다. 이는 문제에서 요구하는 값이 아니며, 적합도를 계산하는 데 활용됩니다. |
| private    | vector&lt;double&gt; geneFitness | 유전자들에 대한 적합도를 담는 벡터입니다. 적합도는 실수로 표현되며, 룰렛 휠 방식을 따릅니다. |
| private    | GeneManager gm                   | GeneManager 클래스 객체입니다.                               |
| private    | RandomManager rm                 | RandomManger 클래스 객체입니다.                              |

### Consturctor

| 이름                             | 설명                                                |
| -------------------------------- | --------------------------------------------------- |
| GeneAlgoManager(int n, int seed) | 유전자 개수를 n으로, 랜덤 시드를 seed로 설정합니다. |

### Functions

| 접근제어자 | 이름                                                     | 설명                                                         |
| ---------- | -------------------------------------------------------- | ------------------------------------------------------------ |
| private    | void CalculateScore(void)                                | GeneManager 클래스의 EvaluateMax를 평가함수로 사용하여 geneScore 벡터에 점수를 채웁니다. |
| private    | double CalculateFitness(void)                            | CalculateScore 함수를 통해 계산된 geneScore 벡터를 활용해 각 유전자의 Fitness, 즉 적합도를 계산해 geneFitness 벡터에 적합도를 채웁니다. |
| private    | int SelectParent(double)                                 | CalculateFitness를 함수를 통해 계산된 geneFitness 벡터를 활용해 룰렛 휠 방식으로 유전자들 중 부모가 될 유전자를 하나 고릅니다. |
| private    | void IndividualCross(Gene& par1, Gene& par2, Gene& res); | par1과 par2를 교차한 결과를 res에 넣습니다.<br />교차 방식은 1번째 유전자에서 임의의 직사각형을 랜덤하게 잡아 그 안을 2번째 유전자로 교체하는 방식입니다. |
| private    | void Cross(void)                                         | elite 변수의 값 만큼 이제까지 나온 것 중 가장 좋은 유전자를 추가합니다.<br />그 후 remain 변수의 값 만큼 기존의 유전자를 추가합니다. 기존의 유전자는 하나가 약 2.5개 삽입됩니다.<br />그 후 남은 유전자는 IndividualCross를 통한 교차를 통해 추가됩니다. |
| private    | void Mutate(void)                                        | 모든 유전자에 대해 ㅎeneManager 클래스의 돌연변이를 적용합니다. |
| private    | void Optimize(void)                                      | 모든 유전자에 대해 GeneManager 클래스의 지역 최적화를 수행합니다. |
| private    | void SaveBestGene(void)                                  | 현재 가장 점수가 높은 유전자와 기존 유전자를 비교해서 더 나은 값을 저장합니다. |
| public     | void NextGeneration(void)                                | 한 세대를 흘립니다.<br />순서는 점수 계산, 최고 유전자 저장, 교차, 돌연변이, 최적화 순서입니다. |
| public     | void PrintBestGene(void)                                 | 현재 최고점을 얻은 유전자를 출력합니다.                      |
| public     | void SaveAllGene(void)                                   | 현재 풀에 있는 모든 유전자를 output.txt에 저장합니다. <br />파일 포맷은 유전자 개수 출력 후 개행, 그 뒤 모든 유전자를 나열합니다. |
| public     | void LoadAllGene(void)                                   | output.txt에서 SaveAllGene과 같은 포맷으로 출력된 유전자를 읽어 와 현재 풀로 대체합니다.<br />예외 처리가 되어 있지 않으니 크기를 반드시 일치시키시길 바랍니다. |