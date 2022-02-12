#include <iostream>
#include <string>

using namespace std;

//Класс звуковоспроизовдящая аппаратура
class SoundEquipment {
protected:
    string name;
    string brand;
    int frequency;
    int serialNumber;
    double price;
public:
    SoundEquipment();
    SoundEquipment(string name, string brand, int frequency, int serialNumber, double price);
    SoundEquipment(const SoundEquipment& s); // копирующий конструктор

    void Сopy(const SoundEquipment& s);

    virtual void SetEquipment(); // Изменение полей объекта класса (делаем его виртуальным, чтобы реализовать полиморфную обработку родственных типов)
    virtual void GetEquipment() const; // Вывод полей объекта (делаем его виртуальным, чтобы реализовать полиморфную обработку родственных типов)
    
    // Геттеры и сеттеры для получения и установки отдельных полей объекта
    void SetName(string name);
    void SetBrand(string brand);
    void SetFrequency(int frequency);
    void SetSerialNumber(int serialNumber);
    void SetPrice(double price);

    string GetName();
    string GetBrand();
    int GetFrequency();
    int GetSerialNumber();
    double GetPrice();

    SoundEquipment& operator=(SoundEquipment& s); // перегрузка оператора присваивания "="
    bool operator>(SoundEquipment& s); // перегрузка оператора сравнения больше ">"
    friend ostream& operator<<(ostream& out, const SoundEquipment& s); // перегрузка оператора вывода "cout << "
};



//Класс акустическая система
class SpeakerSystem : public SoundEquipment {
protected:
    int soundVolume;
public:
    SpeakerSystem() : SoundEquipment(), soundVolume(0) {};

    SpeakerSystem(string name, string brand, int frequency, int serialNumber, double price, int soundVolume) :
        SoundEquipment(name,brand,frequency,serialNumber,price), soundVolume(soundVolume) {};

    void SetEquipment(); // Изменение полей объекта
    void GetEquipment() const; // Вывод полей объекта
};

//Класс портативный плеер
class PortablePlayer: public SpeakerSystem {
protected:
    int workingTime;
public:
    PortablePlayer() : SpeakerSystem(), workingTime(0) {};

    PortablePlayer(string name, string brand, int frequency, int serialNumber, double price, int soundVolume, int workingTime) :
        SpeakerSystem(name, brand, frequency, serialNumber, price, soundVolume), workingTime(workingTime) {};

    void SetEquipment(); // Изменение полей объекта
    void GetEquipment() const; // Вывод полей объекта
};

//Класс система записи звука
class RecorderSystem : public SoundEquipment {
protected:
    string recordType;
public:
    RecorderSystem() : SoundEquipment(), recordType("") {};

    RecorderSystem(string name, string brand, int frequency, int serialNumber, double price, string recordType) :
        SoundEquipment(name, brand, frequency, serialNumber, price), recordType(recordType) {};

    void SetEquipment(); // Изменение полей объекта
    void GetEquipment() const; // Вывод полей объекта
};

//Класс диктофон
class VoiceRecorder : public SpeakerSystem, public RecorderSystem {
protected:
    int recordHours;
public:
    VoiceRecorder() : SpeakerSystem(), RecorderSystem(), recordHours(0) {};

    VoiceRecorder(string name, string brand, int frequency, int serialNumber, double price, int workingTime, string recordType, int recordHours):
        SpeakerSystem(name, brand, frequency, serialNumber, price, workingTime), RecorderSystem(name, brand, frequency, serialNumber, price, recordType),
        recordHours(recordHours) {};

    void SetEquipment(); // Изменение полей объекта
    void GetEquipment() const; // Вывод полей объекта
};

//Класс контейнер
template <class T>
class Vector {
protected:
    int capacity = 0; // Вместимость вектора
    T* arr = NULL; // Сам вектор

public:
    ~Vector(); // Деструктор
    Vector(int Capacity); // Конструктор с параметром
    void ChangeElements(); // Изменение элементов вектора
    void Insert(int index, T elem); // Добавить новый элемент в вектор
    T GetElement(int index);
    void Print() const; // Вывод элементов вектора
    int Size();

    void Search() const; // Поиск
    void Sort(); // Сортировка

};

int main()
{
    setlocale(LC_ALL, "rus");
    

    
    try {
        Vector<PortablePlayer> vecPlayer(1);
        Vector<VoiceRecorder> vecRecorder(1);


        PortablePlayer player("IPod", "Apple", 12000, 223131, 22000.0, 70, 12);

        VoiceRecorder recorder("ДП-12", "Союз", 7000, 123531, 5000.0, 5, "Цифровой", 15);

        vecPlayer.Insert(0, player);
        vecRecorder.Insert(0, recorder);


        vecPlayer.Print();
        vecRecorder.Print();

    }
    catch (const char* ex) {
        cout << "Возникло исключение: " << ex << endl;
    }
}


SoundEquipment::SoundEquipment()
{
    this->name = "";
    this->brand = "";
    this->frequency = 0;
    this->serialNumber = 0;
    this->price = 0.0;
}

SoundEquipment::SoundEquipment(string name, string brand, int frequency, int serialNumber, double price)
{
    this->name = name;
    this->brand = brand;
    this->frequency = frequency;
    this->serialNumber = serialNumber;
    this->price = price;
}



SoundEquipment::SoundEquipment(const SoundEquipment& s)
{
    this->name = s.name;
    this->brand = s.brand;
    this->frequency = s.frequency;
    this->serialNumber = s.serialNumber;
    this->price = s.price;
}

void SoundEquipment::Сopy(const SoundEquipment& s)
{
    this->name = s.name;
    this->brand = s.brand;
    this->frequency = s.frequency;
    this->serialNumber = s.serialNumber;
    this->price = s.price;
}

void SoundEquipment::SetEquipment()
{
    string str;
    cout << "Введите наименование: "; cin >> str;
    this->SetName(str);
    cout << "Введите производителя: "; cin >> str;
    this->SetBrand(str);

    int number;
    cout << "Введите частоту: "; cin >> number;
    this->SetFrequency(number);
    cout << "Введите серийный номер: "; cin >> number;
    this->SetSerialNumber(number);
    double double_number;
    cout << "Введите цену: "; cin >> double_number;
    this->SetPrice(double_number);
}

void SoundEquipment::GetEquipment() const
{
    cout << "Наименование модели: " << this->name << endl;
    cout << "Производитель: " << this->brand << endl;
    cout << "Частота: " << this->frequency << endl;
    cout << "Серийный номер: " << this->serialNumber << endl;
    cout << "Цена: " << this->price << endl;
}

SoundEquipment& SoundEquipment::operator=(SoundEquipment& s)
{
    if (this != &s) {
        this->Сopy(s);
    }
    return *this;
}

bool SoundEquipment::operator>(SoundEquipment& s)
{
    return this->price > s.price;
}

ostream& operator<<(ostream& out, const SoundEquipment& s)
{
    out << "_______________________________________\n";
    out << "Наименование модели: " << s.name << endl;
    out << "Производитель: " << s.brand << endl;
    out << "Частота: " << s.frequency << endl;
    out << "Серийный номер: " << s.serialNumber << endl;
    out << "Цена: " << s.price << endl;
    return out;
}

void SoundEquipment::SetName(string name)
{
    this->name = name;
}

void SoundEquipment::SetBrand(string brand)
{
    this->brand = brand;
}

void SoundEquipment::SetFrequency(int frequency)
{
    this->frequency = frequency;
}

void SoundEquipment::SetSerialNumber(int serialNumber)
{
    this->serialNumber = serialNumber;
}

void SoundEquipment::SetPrice(double price)
{
    this->price = price;
}

string SoundEquipment::GetName()
{
    return this->name;
}

string SoundEquipment::GetBrand()
{
    return this->brand;
}

int SoundEquipment::GetFrequency()
{
    return this->frequency;
}

int SoundEquipment::GetSerialNumber()
{
    return this->serialNumber;
}

double SoundEquipment::GetPrice()
{
    return this->price;
}

void SpeakerSystem::SetEquipment()
{
    SoundEquipment::SetEquipment();
    int soundVolume;
    cout << "Введите громкость: "; cin >> soundVolume;
    this->soundVolume = soundVolume;
}

void SpeakerSystem::GetEquipment() const
{
    SoundEquipment::GetEquipment();
    cout << "Громкость звука: " << this->soundVolume << endl;
}

void PortablePlayer::SetEquipment()
{
    SpeakerSystem::SetEquipment();
    int workingTime;
    cout << "Введите время работы: "; cin >> workingTime;
    this->workingTime = workingTime;
}

void PortablePlayer::GetEquipment() const
{
    SpeakerSystem::GetEquipment();
    cout << "Время работы: " << this->workingTime << endl;
}

void RecorderSystem::SetEquipment()
{
    SoundEquipment::SetEquipment();
    string recordType;
    cout << "Введите тип записи: "; cin >> recordType;
    this->recordType = recordType;
}

void RecorderSystem::GetEquipment() const
{
    SoundEquipment::GetEquipment();
    cout << "Тип записи: " << this->recordType << endl;
}

template<class T>
Vector<T>::~Vector()
{
    delete[] this->arr;
}

template<class T>
Vector<T>::Vector(int Capacity)
{
    if (Capacity > 0) {
        this->capacity = Capacity;
        this->arr = new T[capacity];
    }
    else {
        throw "Ошибка создания вектора. Размер не может отрицательным или равным нулю";
    }
}

template<class T>
void Vector<T>::ChangeElements()
{
    for (int i = 0; i < this->capacity; i++) {
        this->arr[i]->SetEquipment();
    }
}

template<class T>
void Vector<T>::Insert(int index, T elem)
{
    if (this->capacity > index && index >= 0) {
        this->arr[index] = elem;
    }
    else throw "Ошибка добавления элемента в контейнер";
}


template<class T>
T Vector<T>::GetElement(int index)
{
    return this->arr[index];
}

template<class T>
void Vector<T>::Print() const
{
    for (int i = 0; i < capacity; i++) {
        cout << "--------------------------------------\n";
 
            cout << "Элемент #" << i << endl;
            this->arr[i].GetEquipment();
            cout << endl;
        
    }
}

template<class T>
int Vector<T>::Size()
{
    return this->capacity;
}

template<class T>
void Vector<T>::Search() const
{
    string name;
    cout << "ПОИСК\nВведите наименование аппаратуры: "; cin >> name;
    for (int i = 0; i < this->capacity; i++) {
        if (this->arr[i]->GetName() == name) cout << this->arr[i];
    }
}

template<class T>
void Vector<T>::Sort()
{
    for (int i = 0; i < this->capacity - 1; i++) {
        for (int j = i + 1; j < this->capacity; j++) {
            if (arr[i] > arr[j]) {
                T tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }
}

void VoiceRecorder::SetEquipment()
{
    SpeakerSystem::SetEquipment();
    string recordType;
    cout << "Введите тип записи: "; cin >> recordType;
    this->recordType = recordType;

    int recordHours;
    cout << "Введите количество часов записи: "; cin >> recordHours;
    this->recordType = recordHours;
}

void VoiceRecorder::GetEquipment() const
{
    RecorderSystem::GetEquipment();
    cout << "Тип записи: " << this->recordType << endl;
    cout << "Количество часов беспрыервной записи: " << this->recordHours << endl;
    cout << "--------------------------------------\n";

}
