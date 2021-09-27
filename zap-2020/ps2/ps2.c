#include <stdio.h>
#include <math.h>
float lift_a_car(const int stick_length, const int human_weight, const int car_weight);
float unit_price(const float pack_price, const int rolls_count, const int pieces_count);
int collatz(const int number);
int opposite_number(const int n, const int number);
void counter(const int input_array[], const int array_size, int result_array[2]);
unsigned long sum_squared(const int line);
int array_min(const int input_array[], const int array_size);
int array_max(const int input_array[], const int array_size);
unsigned long special_counter(const int input_array[], const int array_size);
int special_numbers(const int input_array[], const int array_size, int result_array[]);

 int main(){
/*	printf("%.4f \n",lift_a_car(2, 80, 1400));
	printf("%.4f \n",lift_a_car(4, 90, 1650));
	printf("%.4f \n",unit_price(4.79, 16, 150));
	printf("%.4f \n",unit_price(5.63, 20, 200));
	printf("%d\n",collatz(20));
	printf("%d\n",collatz(35));
	printf("%d\n", opposite_number(10, 2));
	printf("%d\n", opposite_number(12, 9));
	int input_array[] = {1,2,3,4,5};
	int result_array[2];
	counter(input_array, 5, result_array);
	printf("%d %d\n", result_array[0], result_array[1]);
	// prints: 9 6

	printf("%lu\n", sum_squared(1));
	// prints: 2
	printf("%lu\n", sum_squared(4));
	// prints: 70
	printf("%lu\n", sum_squared(40));
	// prints: 18031015830619195188

	printf("%d\n", array_min(input_array, 5));
	// prints: 1
	printf("%d\n", array_max(input_array, 5));
	// prints: 5
	printf("%d\n", array_max(NULL, 5));
	// prints: -1

	int input_array1[] = {11,12,13,14,15};
    printf("%lu\n", special_counter(input_array1, 5));

    int input_array2[] = {16,17,4,3,5,2};
	int result_array12[6];
	int count = special_numbers(input_array2, 6, result_array12);
	for(int i = 0; i < count; i++){
    	printf("%d ", result_array12[i]);
	}
	printf("\n");
*/
	return 0;
}

// arena, bless u 12/12 pls
/////////////////////////////////////////////////// 1
float lift_a_car(const int stick_length, const int human_weight, const int car_weight){
	return	round((float)stick_length * (float)human_weight /((float)human_weight+ (float)car_weight)*100)/100;
}
/////////////////////////////////////////////////// 2
float unit_price(const float pack_price, const int rolls_count, const int pieces_count){
	return round((100*pack_price/((float)rolls_count*(float)pieces_count))*100)/100 ;
}
/////////////////////////////////////////////////// 3
int collatz(const int number){
	int n = number;
	int i = 1;
	while(n !=1){
		n =	(n%2==0) ? n/2 : 3*n+1;
		i++;
	}
	return i;
}
/////////////////////////////////////////////////// 4
int opposite_number(const int n, const int number){
	return (n/2 >= number) ? n/2 + number : number - n/2;
}
////////////////////////////////////////////////// 5
void counter(const int input_array[], const int array_size, int result_array[2]){
	result_array[0] = input_array[0];
	result_array[1] = input_array[1];
	for(int i = 2; i < array_size; i++){
		 result_array[i%2]+=input_array[i];
	}
}
////////////////////////////////////////////////// 6
unsigned long sum_squared(const int line){
	typedef unsigned long  UNL;
	int row = line+1;

	UNL mult(const int x1 , const  int x2 ){
        UNL mult  = 1;
        int i;
        for(i = x1; i > x2; i--){
            mult = mult *i /(x1-i+1);
                }
        return mult;
    }
	UNL sum = 2;
	UNL c;
	if(row == 2){return 2;}
	if(row % 2 != 0){
		for(int i = 1; i <= ((row-1)/ 2) -1; ++i ){
			c = mult(row-1,row-i-1);
			sum = sum + 2*(c*c);
		}
		c =mult(row-1,(row-1)/2);
		sum = sum +(c*c);
	}else{
		for(int i = 1; i < (row /2) ; ++i){
			UNL  c =mult(row -1,row-i -1);
            sum = sum + 2*(c*c);
		}
	}
	return sum;
}
///////////////////////////////////////////////////// 7
int array_min(const int input_array[], const int array_size){
	if(input_array == NULL){return -1;}
	int min = input_array[0];
	for(int i = 1; i <array_size; ++i){
		min = (min > input_array[i]) ? input_array[i]: min ;
	}
	return min;
}
int array_max(const int input_array[], const int array_size){
    if(input_array == NULL){return -1;}
    int max = input_array[0];
    for(int i = 1; i <array_size; ++i){
        max = (max < input_array[i]) ? input_array[i]: max ;
    }
    return max;
}
///////////////////////////////////////////////////// 8
unsigned long special_counter(const int input_array[], const int array_size){
	unsigned long	sum = 0;
	for(int i= 0; i < array_size ; ++i){
		sum = sum + ((i%2 == 0) ? input_array[i] : input_array[i]*input_array[i]);
	}
	return sum;
}
//////////////////////////////////////////////////// 9
int special_numbers(const int input_array[], const int array_size, int result_array[]){
	int k = 0;
	int sum;
		for(int i = 0; i < array_size ; ++i){
			sum = 0;
			for(int j = i + 1; j <array_size; ++j){
				sum = sum + input_array[j];
			}
			if(input_array[i] > sum){
				result_array[k] = input_array[i];
				k++;
			}
		}
	return k;
}
///////////////////////////////////////////////////// END
