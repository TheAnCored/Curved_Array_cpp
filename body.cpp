#include "header.hpp"

int dance_with_array(const char *filename_input, const char *filename_output){

	FILE *pointer_out;
	FILE *pointer_in;

	List **strings_array;
	
	int rowLen=0;

	int *stringLen;

	// Открываем файл на чтение
	pointer_in = fopen(filename_input, "r");
	if(pointer_in == NULL){
		return -1;
	}

	// Счёт основной длины
	rowLen = reading_rowLen(pointer_in);
	if(rowLen <= 0){
		printf(" The file 'data.txt' is null!\n");
		fclose(pointer_in);

		return -1;
	}
	rewind(pointer_in);


	// Выделяем память для основного массива и массива длин
	strings_array = (List**)malloc(sizeof(List*)*rowLen);
	if(strings_array == NULL){
		printf(" Memory is full!\n");
		fclose(pointer_in);

		return -1;
	}

	stringLen = (int*)malloc(sizeof(int)*rowLen);

    for(int i=0; i<rowLen; i++){
        stringLen[i] = 0;
    }

	// Счёт длин строчек массива
	stringLen = string_len(pointer_in, stringLen, rowLen);


	for(int i=0; i<rowLen; i++){
		strings_array[i] = strings_array[i]->NewList(stringLen[i]);
	}
    free(stringLen);


	// Заполнение массива числами
	strings_array = filling_array(pointer_in, strings_array, rowLen);
	fclose(pointer_in);


	// Функция поиска столбца
	rowLen = search(strings_array, rowLen);


	pointer_out = fopen(filename_output, "w");

	writing_to_file(pointer_out, strings_array, rowLen);
	fclose(pointer_out);

	for(int i=0; i<rowLen; i++){
		strings_array[i]->Delete(strings_array[i]);
	}
	free(strings_array);


	return 0;
}

// Чтение длины строчек
int reading_rowLen(FILE *pointer){

	int rowLen = 0;

	char symb;
	int digit;

	int amount = 0;
	int iter_2 = 0;

	int position_first=0;
	int position_sec=0;

	// Если массив пустой, то вернём 0. Если не пуст - есть хотя бы одна строка
	if(fscanf(pointer, "%d", &digit) != 1){
		return 0;
	}
	else{
		rowLen++;
	}
	rewind(pointer);

	// Посчитаем все числа
	while(fscanf(pointer, "%d", &digit)== 1){
		amount++;
	}
	rewind(pointer);
	
	// Определим начальную позицию в файле
	fscanf(pointer, "%d", &digit);
	position_first = ftell(pointer);


	// Далее будет такой цикл: возьмём положение первого числа в файле,  затем будем между каждыми
	// двумя числами смотреть символ '\n', если такие имеются, то значит мы переходим на новую строчку.
	// Однако, если же таких символов больше одного, то значит пропускаются строчки, поэтому мы прибавим к длине только единицу
	for(int i=0; i<amount-1; i++){

		// Перейдём к следующему числу в файле
		fscanf(pointer, "%d", &digit);
		position_sec = ftell(pointer);


		// Переводим ползунок в файле к первому элементу, чтобы проверить все символы между ними
		fseek(pointer, -1*(position_sec - position_first), 1);

		// Найдём между двумя числами символ перехода на новую строку.
		// Если такого символа нет, то числа в одной строке
		for(int j=position_first; j<position_sec; j++){

			fscanf(pointer, "%c", &symb);

			// Считаем количество переходов на новую строку
			if(symb == '\n'){
				iter_2++;
			}
		}

		// Если между числами есть хоть один переход, то строк больше на единицу
		if(iter_2 > 0){
			rowLen++;
		}
		iter_2 = 0;

		position_first = position_sec;
		position_sec = 0;
	}
	rewind(pointer);

	return rowLen;
}

// Чтение длины каждого внутреннего массива
int *string_len(FILE *pointer, int *stringLen, int rowLen){

    char symb=' ';

    int digit=0;

    int position_first = 0;
    int position_sec = 0;

    int amount=0;

    int iter = 0;
    int check = 0;

    char enter='\n';

    // Введём счётчик, чтобы потом распределить все числа
    while(fscanf(pointer, "%d", &digit)==1){
        amount++;
    }
    rewind(pointer);


    // Если в массиве одна строчка
    if(rowLen == 1){
        while(fscanf(pointer, "%d", &digit)==1){	
            stringLen[0]++;
        }
        rewind(pointer);

        return stringLen;
    }
    else{
	// Перейдём сразу к первому числу в файле так, чтобы ползунок был перед ним
    
    	fscanf(pointer, "%d", &digit);

        for(int i=0; i<rowLen; i++){
                stringLen[i]++;
        }

        position_first = ftell(pointer);

        for(int i=0; i<amount-1; i++){

            fscanf(pointer, "%d", &digit);

            position_sec = ftell(pointer);

            fseek(pointer, -1*(position_sec - position_first), 1);

            for(int j = position_first; j<position_sec; j++){
                    fscanf(pointer, "%c", &symb);

                    if(symb == enter){
                        check=1;
                    }
            }

            if(check == 0){
                    stringLen[iter]++;
            }
            else{
                    iter++;
                    check = 0;
            }

            position_first = position_sec;
        }
    }
    rewind(pointer);

    return stringLen;
}


// Функция заполнения массива
List **filling_array(FILE *pointer, List **strings_array, int rowLen){
	
	int digit;

	// Стандартное заполенение массива целыми числами
    for(int i=0; i<rowLen; i++){
        for(int j=1; j<=strings_array[i]->length_list; j++){
			if(j==1){
				fscanf(pointer, "%d", &digit);

				strings_array[i]->current = strings_array[i]->first;
				strings_array[i]->current->digit = digit;
			}
	        else{
				fscanf(pointer, "%d", &digit);
				strings_array[i]->current = strings_array[i]->current->next_link;
				strings_array[i]->current->digit = digit;
			}
		}
	}	
	rewind(pointer);

	return strings_array;
}

// Функция поиска нужного столбца
int search(List **strings_array, int rowLen){

	int sum=0;

    int max_lenght=0;
	int index=0;

	int check=0;

	for(int i=0;i<rowLen; i++){
		if(strings_array[i]->length_list >= max_lenght){
			max_lenght = strings_array[i]->length_list;
			index = i;
		}
	}

    for(int i=1; i<=strings_array[index]->length_list; i++){
		if(i==1){
			strings_array[index]->current = strings_array[index]->first;
			sum += strings_array[index]->current->digit;
		}
		else{
			strings_array[index]->current = strings_array[index]->current->next_link;
			sum+=strings_array[index]->current->digit;
		}
	}


	if(sum % max_lenght != 0){
		printf("\n В самой длинной строчке нецелое среднее число! \n\n");
		return rowLen;
	}
	

	for(int j=1;j<=max_lenght;j++){

		check = check_column(strings_array, rowLen, j);

		if(check==1){
			
			for(int i=0;i<rowLen;i++){
				strings_array[i]->PopLink(strings_array[i], j);
			}


			for(int i=0; i<rowLen; i++){
				if(strings_array[i]->length_list == 0){
					delete strings_array[i];
					strings_array[i] = nullptr;
				}
			}


			for(int i=0, t=-1; i<rowLen; i++){
				if(strings_array[i]!=nullptr){
					t++;

					if(i!=t){
						strings_array[t] = strings_array[i];
						strings_array[i] = nullptr;
					}
				}
			}


			for(int i=0,iter=0;i<=rowLen;i++){
				if(i<rowLen){
					if(strings_array[i] != nullptr){
						iter++;
					}
				}
				else if(iter != rowLen){
					rowLen = iter;
					strings_array = (List**)realloc(strings_array, sizeof(List*)*iter);
				}
			}

			max_lenght--;
			j--;
			check = 0;
		}
	}
	return rowLen;
}

// Проверка столбца на подходимость условию
int check_column(List **strings_array, int rowLen, int column){

	int sum=0;

	for(int i=0; i<rowLen; i++){

        if((int)strings_array[i]->length_list<column){
			continue;
		}

        for(int j=1; j<=strings_array[i]->length_list; j++){
			if(j==1){
				strings_array[i]->current = strings_array[i]->first;
				sum += strings_array[i]->current->digit;
			}
			else{
				strings_array[i]->current = strings_array[i]->current->next_link;
				sum+=strings_array[i]->current->digit;
			}
		}


		if(sum % strings_array[i]->length_list != 0){
			return 0;
		}

		for(int j=1; j <= column; j++){
			if(j==1){
				strings_array[i]->current = strings_array[i]->first;
			}
			else{
				strings_array[i]->current = strings_array[i]->current->next_link;
			}
		}


        if((int)(sum / strings_array[i]->length_list) != strings_array[i]->current->digit){
			return 0;
		}
		sum=0;
	}

	return 1;
}

// Функция запсис в файл
void writing_to_file(FILE *pointer_out, List **strings_array, int rowLen){

	for(int i=0; i<rowLen; i++){
		if(strings_array[i]->length_list==0){
			continue;
		}
        for(int j=1; j<=strings_array[i]->length_list; j++){
			if(j==1){
				strings_array[i]->current = strings_array[i]->first;
				fprintf(pointer_out, "%d ", strings_array[i]->current->digit);
				printf(" %d ", strings_array[i]->current->digit);
			}
			else{
				strings_array[i]->current = strings_array[i]->current->next_link;
				fprintf(pointer_out, "%d ", strings_array[i]->current->digit);
				printf("%d ", strings_array[i]->current->digit);
			}
		}
		fprintf(pointer_out, "%c", '\n');
		printf("\n");
	}
}