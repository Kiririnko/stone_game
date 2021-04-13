#include <random>
#include <iostream>
#include <chrono>
#include <sstream>

int read_int(const char * question){
		int result;
		std::string inp;
	re: std::cout << question;
		std::getline(std::cin, inp);
		{
			std::stringstream inps {inp};
			inps >> result;
			if (inps.fail()){
				if (std::cin.fail()){
					std::cerr << "Ошибка ввода-вывода!!!" << std::endl;
					exit(1);
				}
				std::cout << "Некорректный ввод!" << std::endl;
				goto re;
			}
		else if (not inps.eof()){
			std::cout << "Непонятный мусор в конце ввода!" << std::endl;
			goto re;
		}
		}
		return result;
}

int read_int_in_range(const char * question, int min, int max){
		int result;
		for(;;){
			result = read_int(question);
			if (result >= min and result <= max) return result;
			std::cout << "Число должно быть в интервале от " << min << " до " << max << std::endl;
		}
		return 0;
}

int main(){
	using clk = std::chrono::system_clock;
	std::minstd_rand rnd {
		unsigned(clk::now().time_since_epoch().count())
	};
	std::uniform_int_distribution<> d {15, 25};
	std::uniform_int_distribution <> d2{1,3};
	unsigned stone_count = d(rnd);
	unsigned stone_comp;
	unsigned int stone;
	unsigned ur;
	ur = read_int_in_range("Выберите уровень сложности:\nEasy - [1]\nHard - [2]\n", 1, 2);
	do{
			std::cout << "В куче " << stone_count << " камней." << std::endl;
			if (stone_count == 0){
				std::cout << "Компьютер проиграл!"<< std::endl;
				break;
			}
			else {
				stone = read_int_in_range("Сколько тянете камней? ", 1, std::min(3U,stone_count));
				stone_count-=stone;
			}
			if (stone_count == 0){
				std::cout << "Вы проиграли!"<< std::endl;
				break;
			}
			else {
				if (stone_count > 3 && ur == 1){
					stone_comp = d2(rnd);
					std::cout << "Компьютер взял " << stone_comp << " камня." << std::endl;
					stone_count-=stone_comp;
				}
				else if ((stone_count > 12 || stone_count == 5 || stone_count == 9) && ur == 2){
					stone_comp = d2(rnd);
					std::cout << "Компьютер взял " << stone_comp << " камня." << std::endl;
					stone_count-=stone_comp;
				}
				else if (ur == 2 && (stone_count == 4 || stone_count == 8 || stone_count == 12)){
					stone_comp = 3;
					std::cout << "Компьютер взял " << stone_comp << " камня." << std::endl;
					stone_count-=stone_comp;
				}
				else if (ur == 2 && (stone_count == 3 || stone_count == 7 || stone_count == 11)){
					stone_comp = 2;
					std::cout << "Компьютер взял " << stone_comp << " камня." << std::endl;
					stone_count-=stone_comp;
				}
				else if (ur == 2 && (stone_count == 2 || stone_count == 6 || stone_count == 10)){
					stone_comp = 1;
					std::cout << "Компьютер взял " << stone_comp << " камень." << std::endl;
					stone_count-=stone_comp;
				}
				else {
					int a = stone_count;
					std::uniform_int_distribution <> c{1, a};
					stone_comp = c(rnd);
					std::cout << "Компьютер взял " << stone_comp << " камня." << std::endl;
					stone_count-=stone_comp;
				}
			}
	} while(true);
	return 0;
}
