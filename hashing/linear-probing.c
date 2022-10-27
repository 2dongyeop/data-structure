//해시 테이블은 1차원 배열로 구현된다.
#define KEY_SIZE 10
#define TABLE_SIZE 13

typedep struct {
		char key[KEY_SIZE];
		//기타 필드들
} element;

element hash_table[TABLE_SIZE];


//해시 테이블의 각 요소들은 초기화 과정을 거쳐야 한다. (공백상태로 만들기)
void init_table(element ht[]) {
		int i;
		for (i = 0; i < TABLE_SIZE; i++) {
				ht[i].key[0] = NULL;
		}
}


//해시 테이블에 키를 삽입하기 위해서는 키를 정수로 바꾸는 해시 함수가 필요하다.
//여기서는 문자열을 먼저 정수로 바꾸고, 여기에 다시 제산 함수를 적용시킨다.
//문자열의 각 문자 아스키 코드를 전부 합하는 방식을 사용한 것은 -> 설명을 쉽게하기 위함.
int transform(char *key) {
		int number = 0;
		while (*key)
				number = 31 * number + *key++;
		return number;
}

int hash_function(char *key) {
		return transform(key) % TABLE_SIZE;
}

#define empty(item) (strlen(item.key)) == 0)
#define equal(item1, item2) (!strcmp(item1.key, item2.key))


//선형 조사법을 이용하여 테이블에 키를 삽입
//테이블이 가득 찬 경우는 종료
void hash_lp_add(element item, element ht[]) {
		int i, hash_value;
		hash_value = i = hash_function(item.key);

		while(!empty(ht[i])) {
				if (equal(item, ht[i])) {
						fprintf(stderr, "탐색키가 중복되었습니다.\n");
						exit(1);
				}
				i = (i + 1) % TABLE_SIZE;
				if (i == hash_value) {
						fprintf(stderr, "테이블이 가득찼습니다.\n");
						exit(1);
				}
		}
		ht[i] = item;
}


//선형조사법을 이용하여 테이블에 저장된 키를 검색
void hash_lp_search(element item, element ht[]) {
		int i, hash_value;
		hash_value = i = hash_function(item.key);
		while (!empty(item, ht[i])) {
				if (equal(item, ht[i])) {
							fprintf(stderr, "탐색. %s: 위치 = %d\n", item.key, i);
							return;
				}
				i = (i + 1) % TABLE_SIZE;
				if (i == hash_value) {
						fprintf(stderr, "찾는 값이 테이블에 없음.\n");
						return;
				}
		}
		fprintf(stderr, "찾는 값이 테이블에 없음.\n");
}