#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::vector;
using std::string;
using std::sort;
using std::endl, std::cout, std::cin;

struct rotation
{
    string text;
    int rotated_piece_start_pos;
    int rotated_piece_size;
};



vector<string> read_phrases(vector<string> & phrases);
void make_rotations(const string & original_phrase, vector<rotation> & rotations);
bool compare(rotation const & r1, rotation const & r2);
void print_kwic(vector<string> phrases);




int main()
{
    vector<string> phrases;
    read_phrases(phrases);
    print_kwic(phrases);
    
    return 0;
}

void print_kwic(vector<string> phrases)
{

    // Вектор для хранения циклических сдвигов
    vector<rotation> rotations;

    // Фраза
    string phrase;

    // Генерация циклических сдвигов
    for (vector<string>::const_iterator phrase_it = phrases.begin(); phrase_it != phrases.end(); ++phrase_it)
    {
        phrase = *phrase_it;
        make_rotations(phrase, rotations);
    }
    

    // Сортировка циклических сдвигов
    sort(rotations.begin(), rotations.end(), compare);

    // Поиск самого длинного kwic-индекса
    int max_kwic_size = 0;
    rotation phrase_rotation;

    for (vector<rotation>::const_iterator rot_it = rotations.begin(); rot_it != rotations.end(); ++rot_it)
    {
        phrase_rotation = *rot_it;
       
       if (phrase_rotation.rotated_piece_size > max_kwic_size)
       {
            max_kwic_size = phrase_rotation.rotated_piece_size;
       }
    }

    // Вывод kwic-индекса
    string kwic;

    for (vector<rotation>::const_iterator rot_it = rotations.begin(); rot_it != rotations.end(); ++rot_it)
    {
        phrase_rotation = *rot_it;
        kwic = phrase_rotation.text.substr(phrase_rotation.rotated_piece_start_pos, phrase_rotation.rotated_piece_size);

        cout << kwic + string(max_kwic_size + 1 - kwic.size(),' ') <<  phrase_rotation.text.substr(0, phrase_rotation.rotated_piece_start_pos) << endl;
    } 
}



// Построчное чтение фраз
vector<string> read_phrases(vector<string> & phrases)
{
    string phrase;

    while(getline(cin, phrase))
    {
        if (phrase.empty())
        {
            break;
        }
        
        phrases.push_back(phrase);
    }

    return phrases;
}


void make_rotations(const string & original_phrase, vector<rotation> & rotations)
{
    // Инициалищация исходной фразой
    string shifted_line = original_phrase;
    // Сдвинутая часть строки
    string rotated_part;
    // Размер исходной строки
    int original_size = original_phrase.size();
    
    // Сдвинутая фраза
    rotation rotated_phrase;

    // Тождественный сдвиг (ничего не делаем)
    rotated_phrase.text = original_phrase;
    rotated_phrase.rotated_piece_start_pos = original_size;
    rotated_phrase.rotated_piece_size = 0;
    rotations.push_back(rotated_phrase);


    // Генерация циклических сдвигов
    for (string::size_type i = 0; i < original_size; ++i)
    {
        // Если дошли до пробела
        if (original_phrase[i] == ' ')
        {
            // Получаем кусок, котррвый нужно сдвинуть
            rotated_part = original_phrase.substr(0, i);
            // Получаем сдвинутую фразу
            rotated_phrase.text = original_phrase.substr(i + 1, original_size) + " " + rotated_part;
            // Получаем позицию и размер сдвинутого куска
            rotated_phrase.rotated_piece_start_pos = original_size - rotated_part.size();
            rotated_phrase.rotated_piece_size = rotated_part.size() + 1;
            // Сохраняем текущий сдвиг
            rotations.push_back(rotated_phrase);
        }
    }
}


bool compare(rotation const & r1, rotation const & r2){
    return r1.text < r2.text;
}