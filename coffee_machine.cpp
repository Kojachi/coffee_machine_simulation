#include <iostream>
#include <vector>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <windows.h>
using namespace std;

int price, portion;//ціна та к-сть напою

class Energy {//система електроподачі
    bool power; //автомат вимкнен/увімкнен
    int voltage;//напруга
public:
    void on();//ф-ція уввімкнення
    void off();//ф-ція вимкнення
    bool getPower();//ф-ція повернення значення напруги
    Energy() {//конструктор
        power = false;
    }
};
void Energy::on() {
    voltage = (15 + rand() % 15) * 10;//рандомне значення напруги
    if (voltage < 220 or voltage > 270) {//якщо вона не підходить під вимоги
        if (voltage <= 220) {//повідомляємо що занадто мале значення
            cout << "Voltage: " << voltage << "V" << endl;
            cout << "There is not enough voltage" << endl;
        }
        else {//або занадто велике
            cout << "Voltage: " << voltage << "V" << endl;
            cout << "Too much voltage" << endl;
        }
        power = false;
    }
    else {//при відповідному значенні
        cout << "Voltage: " << voltage << "V" << endl;
        cout << "*Energy is on*" << endl;
        power = true;//включаємо автомат
    }
}
void Energy::off() {
    cout << "*Energy is off*" << endl;
    voltage = 0;
    power = false;//вимикаємо автомат
}
bool Energy::getPower() {
    on();
    return power;
}

class Coffee {//клас напоїв
    int priceForPortion;//ціна за порцію
    string bvr;//назва напою
public:
    int countOfPortion;//к-сть порцій в автоматі
    Coffee(int price, int count, string name) {//конструктор створення об'єктів класу
        priceForPortion = price;
        countOfPortion = count;
        bvr = name;
    }
    int getPrice() {//ф-ція, що повертає ціну за порцію
        return priceForPortion;
    }
    int getPortion() {//ф-ція, що повертає к-сть порцій
        return countOfPortion;
    }
    string getName() {//ф-ція, що повертає назву напою
        return bvr;
    }
    int minusPortion();//ф-ція, що зменшує к-сть залишених порцій
};
int Coffee::minusPortion() {
    countOfPortion--;
    return countOfPortion;
}

class cashSystem {//касова система
    int balance = 0;//грошовий баланс 
public:
    int income = 0;//дохід адміна
    void update(int sum);//ф-ція поповнення поточного балансу
    bool subtraction(Coffee* thing);//ф-ція перевірки поточного балансу та ціни за відповідний напій
    int getBalance() {//ф-ція виведення поточного балансу
        return balance;
    }
    int rest();//ф-ція, що повертає решту
    int getIncome();//ф-ція, що повертає дохід
};
void cashSystem::update(int sum) {
    balance = balance + sum;
}
bool cashSystem::subtraction(Coffee* thing) {
    int priceForBvr = thing->getPrice();//ціна за обраний напій
    if (balance < priceForBvr) {//якщо грошей на балансі менше, ніж ціна напою
        return false;//повертає значення false
    }
    else {//якщо грошей достатньо
        balance = balance - priceForBvr;//з балансу віднімається сума за обраний напій
        income = income + priceForBvr;//нараховується дохід
        return true;//повертає значення true
    }
}
int cashSystem::rest() {
    int temp = balance;
    balance = 0;//після повернення решти поточний баланс обнуляється
    return temp;
}
int cashSystem::getIncome() {
    int temp = income;
    income = 0;//після отримання доходу сума обнуляється
    return temp;
}

class waterHeatingSystem {//система нагріву води
    int water = 0;//к-сть води(ml)
    int usedWater = 0;//к-сть використанної води(ml)
public:
    int amountOfWater(Coffee* thing);//ф-ція використання води для певного напою
    int heatenWater() {//ф-ція, що повертає к-сть використанної води
        return usedWater;
    }
    int getWater() {//ф-ція, що повертає к-сть води в автоматі
        return water;
    }
    void heating() {//ф-ція нагріву води
        cout << "-Water is boiling..." << endl;
    }
    void refreshWater(int quant);//ф-ція поповнення запасів води
};
void waterHeatingSystem::refreshWater(int quant) {
    water = water + quant * 1000;//заливання пляшок води в автомат
    cout << "*+" << quant << " bottles of water*" << endl;
}
int waterHeatingSystem::amountOfWater(Coffee* thing) {
    if (thing->getName() == "espresso") {//для еспрессо
        if (water >= 30) {//використовується 30ml води 
            water = water - 30;
            usedWater = 0;
            usedWater = usedWater + 30;//записуємо значення використанної к-сті води
            return water;
        }
        else {//якщо в автоматі менше води, ніж потрібно для напою
            cout << "*Don't enough water*" << endl;
            return -1;//повертаємо значення "false"
        }
    }
    else if (thing->getName() == "cocoa") {//для какао
        if (water >= 300) {//використовується 300ml води 
            water = water - 300;
            usedWater = 0;
            usedWater = usedWater + 300;
            return water;
        }
        else {
            cout << "*Don't enough water*" << endl;
            return -1;
        }
    }
    else if (thing->getName() == "americano") {//для амерікано
        if (water >= 250) {//використовується 250ml води 
            water = water - 250;
            usedWater = 0;
            usedWater = usedWater + 250;
            return water;
        }
        else {
            cout << "*Don't enough water*" << endl;
            return -1;
        }
    }
    else if (thing->getName() == "latte") {//для латте
        if (water >= 300) {//використовується 300ml води 
            water = water - 300;
            usedWater = 0;
            usedWater = usedWater + 300;
            return water;
        }
        else {
            cout << "*Don't enough water*" << endl;
            return -1;
        }
    }
}

class cookingSystem {//система приготування
    int cups = 0;//к-сть паперових стаканчиків
    int quantOfSugar = 0;//к-сть цукру в автоматі(g)
    int usedSugar = 0;//к-сть використанного цукру(g)
public:
    int getCup() {//ф-ція, що повертає к-сть стаканчиків в автоматі
        return cups;
    }
    int getS() {//ф-ція, що повертає к-сть цукру в автоматі
        return quantOfSugar;
    }
    int getSugar() {//ф-ція, що повертає к-сть використанного цукру
        return usedSugar;
    }
    void refreshCups(int quant);//ф-ція поповнення запасів стаканчиків
    void refreshSugar(int quant);//ф-ція поповнення запасів цукру
    void nullify();//ф-ція обнулення рівню цукру
    int minusCup();//ф-ція, що зменшує к-сть залишених стаканчиків
    int minusSugar(int level);//ф-ція, що зменшує к-сть цукру в автоматі(але збільшує рівень цукру в напої)
    int minusSugar();//ф-ція, що збільшує к-сть цукру в автоматі(але зменшує рівень цукру в напої)
    void paperCup();//ф-ція, що видає стаканчик
    void fillMixture(Coffee* thing);//ф-ція, що насипає суміш
    void addSugar(int level);//ф-ція, що додає цукор до напою
    void rmSugar();//ф-ція, що зменшує рівень цукру в напої
    void hotWater(waterHeatingSystem* thing);//ф-ція заливання нагрітої води
};
void cookingSystem::refreshCups(int quant) {
    cups = cups + quant;
    cout << "*+" << quant << " paper cups*" << endl;
}
void cookingSystem::refreshSugar(int quant) {
    quantOfSugar = quantOfSugar + quant * 200;
    cout << "*+" << quant << " packs of sugar*" << endl;
}
void cookingSystem::nullify() {
    usedSugar = 0;
}
int cookingSystem::minusCup() {
    cups--;
    return cups;
}
int cookingSystem::minusSugar(int level) {//ф-ція, що зменшує к-сть цукру в автоматі(але збільшує рівень цукру в напої)
    if (level == 1) {//при обиранні low-sugar
        quantOfSugar = quantOfSugar - 5;//додається 5г цукру до напою
        //і відповідно к-сть цукру в автоматі зменшується
        usedSugar = usedSugar + 5;
    }
    else if (level == 2) {//при обиранні high-sugar
        quantOfSugar = quantOfSugar - 10;//додається 10г цукру до напою
        usedSugar = usedSugar + 10;
    }
    return quantOfSugar;
}
int cookingSystem::minusSugar() {//ф-ція, що збільшує к-сть цукру в автоматі(але зменшує рівень цукру в напої)
    quantOfSugar = quantOfSugar + 5;
    return quantOfSugar;
}
void cookingSystem::paperCup() {//ф-ція, що видає стаканчик
    cout << "*Left paper cups: " << minusCup() << "*" << endl;//виклик ф-ції, що зменшує к-сть стаканчиків в автоматі
    //Sleep(2000);
    cout << "-The paper cup is given-" << endl;
}
void cookingSystem::fillMixture(Coffee* thing) {//ф-ція, що насипає суміш
    cout << "*Left " << thing->getName() << "'s mixture: " << thing->minusPortion() << "*" << endl;//виклик ф-ції, що зменшує 
    //к-сть обраної порошкової кави
    cout << "-Powder is poured into paper cup-" << endl;
}
void cookingSystem::addSugar(int level) {
    if (level == 1 and getSugar() < 10 and quantOfSugar >= 5) {//якщо обран рівень low-sugar
        cout << "- +1 tea spoon of sugar" << endl;
        cout << "*Left quantity of sugar: " << minusSugar(level) << "*" << endl;
    }
    else if (level == 2 and getSugar() == 0 and quantOfSugar >= 10) {//якщо обран рівень high-sugar
        cout << "- +2 tea spoon of sugar" << endl;
        cout << "Left quantity of sugar: " << minusSugar(level) << "*" << endl;
    }
    else if (level == 0) {//якщо обран рівень без цукру
        cout << "-No sugar" << endl;
    }
    else {//максимальна к-ість цукру в напої 10г(або один high-sugar, або два low-sugar)
        cout << "-You cannot add more" << endl;
    }
}
void cookingSystem::rmSugar() {//ф-ція, що зменшує рівень цукру в напої
    cout << "- -1 tea spoon of sugar" << endl;
    usedSugar = usedSugar - 5;
    cout << "*Left quantity of sugar: " << minusSugar() << "*" << endl;
}
void cookingSystem::hotWater(waterHeatingSystem* thing) {//ф-ція заливання нагрітої води
    cout << "*" << thing->heatenWater() << "ml of water is poured into paper cup*" << endl;
}

class Admin {//клас адміна
    double budget = 100.0;//бюджет адміна
public:
    void turn_on(Energy* thing) {//ф-ція уввімкнення автомату
        bool onf = thing->getPower();
        while (onf == false) {
            cout << "*Setting the Voltage*" << endl;
            onf = thing->getPower();
        }
    }
    void turn_off(Energy* thing) {//ф-ція вимкнення автомату
        thing->off();
    }
    void getMoney(cashSystem* thing) {//ф-ція отримання доходу з автомату
        budget = budget + thing->getIncome();
    }
    double getBudget() {//ф-ція, що повертає бюджет адміна
        return budget;
    }
    bool buyCups(cookingSystem* thing, int quant) {//ф-ція закупівлі паперових стаканчиків
        if (budget >= 0.5 * quant) {
            thing->refreshCups(quant);
            budget = budget - 0.5 * quant;
            return true;
        }
        else {
            return false;
        }
    }
    bool buySugar(cookingSystem* thing, int quant) {//ф-ція закупівлі упаковок цукру
        if (budget >= 0.2 * quant) {
            thing->refreshSugar(quant);
            budget = budget - 0.2 * quant;
            return true;
        }
        else {
            return false;
        }
    }
    bool buyWater(waterHeatingSystem* thing, int quant) {//ф-ція закупівлі пляшок води
        if (budget >= 0.6 * quant) {
            thing->refreshWater(quant);
            budget = budget - 0.6 * quant;
            return true;
        }
        else {
            return false;
        }
    }
    bool buyPowders(int quant, int price) {//ф-ція закупівлі упаковок порошкової кави
        if (budget >= price * quant) {
            budget = budget - price * quant;
            return true;
        }
        else {
            return false;
        }
    }
};

class Machine {//система кавовий автомат
public:
    cashSystem cash;
    //controlSystem control;
    class controlSystem {
    public:
        bool heatWater(waterHeatingSystem* a, Coffee* b);//ф-ція нагріву води
        void servePaperCup(cookingSystem* a, waterHeatingSystem* b, Coffee* c);//ф-ція подачі напою
        bool chosenBvr(cashSystem* a, Coffee* b);//ф-ція перевірки достатньої к-сті грошей на балансі
        int calculOfRest(cashSystem* a);//ф-ція обрахування решти
    };
    controlSystem control;
    cookingSystem cook;
    waterHeatingSystem whs;
    Energy energy;
};
bool Machine::controlSystem::chosenBvr(cashSystem* a, Coffee* b) {
    if (a->subtraction(b) == true) {//якщо на балансі достатньо грошей для напою
        return true;//напій можна почати готувати
    }
    else {//на балансі недостатньо грошей 
        cout << "-You don't have enough money on current balance" << endl;
        return false;//клієнта повідомляють про це
    }
}
bool Machine::controlSystem::heatWater(waterHeatingSystem* a, Coffee* b) {
    int water = a->amountOfWater(b);//виклик ф-ції, що повертає значення потрібної к-сть води для напою
    if (water != -1) {//якщо води в автоматі достатньо
        cout << "*Left water: " << water << "ml*" << endl;
        a->heating();//то вода нагрівається
        return true;
    }
    else {//якщо недостатньо
        return false;//клієнта повідомляють про це
    }
}
int Machine::controlSystem::calculOfRest(cashSystem* a) {
    int money = a->rest();//виклик ф-ції, що обраховує решту
    if (money == 0) {//якщо решта==0
        return 0;//решти нема
    }
    else {//в іншому випадку клієнту повертається його решта
        return money;
    }
}
void Machine::controlSystem::servePaperCup(cookingSystem* a, waterHeatingSystem* b, Coffee* c) {//ф-ція подачі напою
    a->paperCup();//виклик ф-ції, що видає стаканчик
    a->fillMixture(c);//виклик ф-ції, що засипає суміш
    int choice1 = 0;
    while (choice1 != 3) {//екран з маніпуляціми над рівнем цукру в напої
        cout << "-Level of sugar: " << a->getSugar() << "g" << endl;
        cout << "1.Add sugar" << endl;
        cout << "2.Remove sugar" << endl;
        cout << "3.End" << endl;
        cin >> choice1;
        switch (choice1) {
        case 1://якщо обрано додати цукор
            cout << "-There is three level of sugar:" << endl;//екран з рівнями цукру
            cout << "0.Zero sugar" << endl;
            cout << "1.Low-sugar" << endl;
            cout << "2.High-sugar" << endl;
            int choice2;
            cin >> choice2;
            while (choice2 != 0 and choice2 != 1 and choice2 != 2) {
                cin >> choice2;
            }
            a->addSugar(choice2);//виклик ф-ції з додаванням потрібного рівню цукру
            break;
        case 2://якщо обрано зменшити рівень цукру
            if (a->getSugar() > 0) {
                a->rmSugar();//виклик ф-ції, що зменшує рівень цукру на 5г
            }
            else {//якщо цукру й так нема
                cout << "-There is already no sugar" << endl;//нема що зменшувати
            }
            break;
        case 3://кінець маніпуляцій з цукром
            cout << "*" << a->getSugar() << "g of sugar is poured into paper cup*" << endl;
            a->nullify();
            break;
        default:
            cout << "-Wrong input. Try again" << endl;
            break;
        }
    }
    a->hotWater(b);//виклик ф-ції, що нагріває воду
}

class Customer {//клас клієнта
public:
    int money;//бюджет клієнта
    Customer(int x) {//конструктор створення об'єктів класу
        money = x;
    }
    int budget() {//ф-ція що повертає бюджет клієнта
        return money;
    }
    void setMoney(int sum) {//ф-ція, що встановлює бюджет клієнта
        money = sum;
    }
    void enterMoney(cashSystem* thing);//ф-ція введення грошей в автомат
    bool chooseBvr(Machine* a, cashSystem* b, Coffee* c);//ф-ція вибору напою
    int getRest(Machine* a, cashSystem* b);//ф-ція отримання решти
};
void Customer::enterMoney(cashSystem* thing) {
    int enteredSum;
    cout << "-How much money do you want to enter?: " << endl;
    cin >> enteredSum;
    while (enteredSum > money) {
        cout << "-You don't have enough money" << endl;
        cout << "-How much money do you want to enter?: " << endl;
        cin >> enteredSum;
    }
    money = money - enteredSum;
    thing->update(enteredSum);
}
bool Customer::chooseBvr(Machine* a, cashSystem* b, Coffee* c) {
    return a->control.chosenBvr(b, c);
}
int Customer::getRest(Machine* a, cashSystem* b) {
    int rest = a->control.calculOfRest(b);
    if (rest != 0) {
        money = money + rest;
        return rest;
    }
    else {
        return 0;
    }
}

void preparations(Machine* coffeeMachine, Admin* admin) {//ф-ція закупівлі необхідних продуктів
    cout << "Admin's budget: " << admin->getBudget() << "$" << endl;
    int quant;
    if (coffeeMachine->cook.getCup() == 0) {//перевірка на наявність паперових стаканчиків в автоматі
        cout << "There is no paper cups in coffee machine. Admin needs to buy some" << endl;
        cout << "How many?(1 cup = 0.5$): ";
        cin >> quant;
        while (quant <= 0 or quant > 100) {//перевірки на від'ємні та занадто великі значення
            if (quant < 0) {
                cout << "You cannot use the negative numbers" << endl;
            }
            else {
                cout << "You cannot use more than 100 cups in one machine" << endl;
            }
            cout << "Try again: ";
            cin >> quant;
        }
        bool check = false;
        while (check == false) {
            check = admin->buyCups(&coffeeMachine->cook, quant);//чи достатньо грошей у адміна для закупівлі стаканчиків? 
            if (check == false and quant != 1) {//недостатньо для заданої к-сті
                cout << "Admin doesn't have enough money. Try to buy fewer paper cups: ";
                cin >> quant;
                while (quant <= 0 or quant > 100) {
                    if (quant < 0) {
                        cout << "You cannot use the negative numbers" << endl;
                    }
                    else {
                        cout << "You cannot use more than 100 cups in one machine" << endl;
                    }
                    cout << "Try again: ";
                    cin >> quant;
                }
            }
            else if (check == false and quant == 1) {//недостатньо навіть для одного стаканчику
                cout << "Business is unprofitable" << endl;
                cout << "GAME OVER" << endl;
                exit(0);//завершення програми, бо адмін - банкрут
            }
            else {
                cout << "Admin's budget: " << admin->getBudget() << "$" << endl;
            }
        }
    }
    if (coffeeMachine->cook.getS() <= 10) {//все теж саме, але з упаковками цукру
        cout << "There is no sugar in coffee machine. Admin needs to buy some" << endl;
        cout << "How many?(1 pack(200g) = 0.2$): ";
        cin >> quant;
        while (quant <= 0 or quant > 5) {
            if (quant < 0) {
                cout << "You cannot use the negative numbers" << endl;
            }
            else {
                cout << "You cannot use more than 1kg of sugar in one machine" << endl;
            }
            cout << "Try again: ";
            cin >> quant;
        }
        bool check = false;
        while (check == false) {
            check = admin->buySugar(&coffeeMachine->cook, quant);
            if (check == false and quant != 1) {
                cout << "Admin doesn't have enough money. Try to buy fewer packs: ";
                cin >> quant;
                while (quant <= 0 or quant > 5) {
                    if (quant < 0) {
                        cout << "You cannot use the negative numbers" << endl;
                    }
                    else {
                        cout << "You cannot use more than 1kg of sugar in one machine" << endl;
                    }
                    cout << "Try again: ";
                    cin >> quant;
                }
            }
            else if (check == false and quant == 1) {
                cout << "Business is unprofitable" << endl;
                cout << "GAME OVER" << endl;
                exit(0);
            }
            else {
                cout << "Admin's budget: " << admin->getBudget() << "$" << endl;
            }
        }
    }
    if (coffeeMachine->whs.getWater() < 300) {//теж саме з водою
        cout << "There is no water in coffee machine. Admin needs to buy some" << endl;
        cout << "How many?(1 bottle(1l) = 0.6$): ";
        cin >> quant;
        while (quant <= 0 or quant > 5) {
            if (quant < 0) {
                cout << "You cannot use the negative numbers" << endl;
            }
            else {
                cout << "You cannot use more than 5l of water in one machine" << endl;
            }
            cout << "Try again: ";
            cin >> quant;
        }
        bool check = false;
        while (check == false) {
            check = admin->buyWater(&coffeeMachine->whs, quant);
            if (check == false and quant != 1) {
                cout << "Admin doesn't have enough money. Try to buy fewer bottles: ";
                cin >> quant;
                while (quant <= 0 or quant > 5) {
                    if (quant < 0) {
                        cout << "You cannot use the negative numbers" << endl;
                    }
                    else {
                        cout << "You cannot use more than 5l of water in one machine" << endl;
                    }
                    cout << "Try again: ";
                    cin >> quant;
                }
            }
            else if (check == false and quant == 1) {
                cout << "Business is unprofitable" << endl;
                cout << "GAME OVER" << endl;
                exit(0);
            }
            else {
                cout << "Admin's budget: " << admin->getBudget() << "$" << endl;
            }
        }
    }
}

void freshenDrinks(Admin* admin, int pr, int po) {//ф-ція закупівлі усіх видів порошкової кави
    int quant;
    cin >> quant;
    while (quant <= 0 or quant > 12) {//перевірка на некоректні значення
        if (quant < 0) {
            cout << "You cannot use the negative numbers" << endl;
        }
        else {
            cout << "You cannot buy more than 12" << endl;
        }
        cout << "Try again: ";
        cin >> quant;
    }
    bool check = false;
    while (check == false) {
        check = admin->buyPowders(quant, pr);
        if (check == false and quant != 1) {//перевірка на наявність даного виду кави
            cout << "Admin doesn't have enough money. Try to buy fewer packs: ";
            cin >> quant;
            while (quant <= 0 or quant > 12) {
                if (quant < 0) {
                    cout << "You cannot use the negative numbers" << endl;
                }
                else {
                    cout << "You cannot buy more than 12" << endl;
                }
                cout << "Try again: ";
                cin >> quant;
            }
        }
        else if (check == false and quant == 1) {//якщо нема грошей
            cout << "Business is unprofitable" << endl;
            cout << "GAME OVER" << endl;
            exit(0);//адмін - банкрут
        }
        else {
            cout << "Admin's budget: " << admin->getBudget() << "$" << endl;
        }
    }
    po = 6 * quant;//к-сть порцій в одній упаковці
    portion = po;
    cout << "What is the price for it?(5-15$): ";
    cin >> pr;//назначаємо ціну для певного напою
    while (pr > 15 or pr < 5) {//перевірка на завелику та замаленьку ціни
        if (pr > 15) {
            cout << "It's too expensive" << endl;
        }
        else {
            cout << "It's too cheap" << endl;
        }
        cout << "Try again(5-15$): ";
        cin >> pr;
    }
    price = pr;
}

int freshenPowders(Admin* admin, int pr, int po) {//ф-ція закупівлі необхідних видів порошкової кави
    int quant;
    cin >> quant;
    while (quant <= 0) {
        cout << "You cannot use the negative numbers" << endl;
        cout << "Try again: ";
        cin >> quant;
    }
    bool check = false;
    while (check == false) {
        check = admin->buyPowders(quant, pr);
        if (check == false and quant != 1) {
            cout << "Admin doesn't have enough money. Try to buy fewer packs: ";
            cin >> quant;
            while (quant <= 0) {
                cout << "You cannot use the negative numbers" << endl;
                cout << "Try again: ";
                cin >> quant;
            }
        }
        else if (check == false and quant == 1) {
            cout << "Business is unprofitable" << endl;
            cout << "GAME OVER" << endl;
            exit(0);
        }
        else {
            cout << "Admin's budget: " << admin->getBudget() << "$" << endl;
        }
    }
    po = 6 * quant;
    return po;
}

int main() {
    srand(time(NULL));//генерація різних рандомних значень
    Admin admin;//ініціалізація об'єкта классу Адмін
    Machine coffeeMachine;//ініціалізація об'єкта классу Кавовий апарат
    
    preparations(&coffeeMachine, &admin);//виклик ф-ції поповнення запасів
    cout << "Beverages that we need to freshen: " << endl;
    cout << "1.Espresso" << endl;
    cout << "2.Cocoa" << endl;
    cout << "3.Americano" << endl;
    cout << "4.Latte" << endl;

    cout << "Admin needs to buy ESPRESSO's powder" << endl;
    cout << "How many?(1 pack(6 portions) = 2$): ";
    price = 2;
    freshenDrinks(&admin, price, portion);//виклик ф-ції закупівлі порошкової кави(еспресо) 
    Coffee espresso(price, portion, "espresso");//об'єкт классу створений за конструктором, у якому є:
    //ціна за напій, к-сть цього напою, та назва напою

    cout << "Admin needs to buy COCOA's powder" << endl;
    cout << "How many?(1 pack(6 portions) = 2$): ";
    price = 2;
    freshenDrinks(&admin, price, portion);//теж саме для какао
    Coffee cocoa(price, portion, "cocoa");

    cout << "Admin needs to buy AMERICANO's powder" << endl;
    cout << "How many?(1 pack(6 portions) = 3$): ";
    price = 3;
    freshenDrinks(&admin, price, portion);//для амерікано
    Coffee americano(price, portion, "americano");

    cout << "Admin needs to buy LATTE's powder" << endl;
    cout << "How many?(1 pack(6 portions) = 4$): ";
    price = 4;
    freshenDrinks(&admin, price, portion);//для латте
    Coffee latte(price, portion, "latte");

    cout << "-------------------------------------------" << endl;

    vector<Customer> clients;//створюємо вектор з об'єктів класу Клієнт
    vector<int> budgets;//та створюємо вектор із бюджета
    int sum, cust;
    int counter = 0;//лічильник клієнтів
    int drink;
    int e = 0;//к-сть купленого клієнтом еспресо
    int c = 0;//к-сть купленого клієнтом какао
    int a = 0;//к-сть купленого клієнтом амерікано
    int l = 0;//к-сть купленого клієнтом латте
    string agree;
    bool cycle;
    while (true) {//нескінченний цикл
        admin.turn_on(&coffeeMachine.energy);//адмін включає апарат(використовуючи клас енергопостачання)
        while (coffeeMachine.cook.getCup() > 0 and coffeeMachine.whs.getWater() > 300 and (espresso.getPortion() > 0 or cocoa.getPortion() > 0 or americano.getPortion() > 0 or latte.getPortion() > 0)) {
            //якщо в автоматі є стаканчики, і є вода(більше ніж 300мл), і є хоча б одна порція будь-якого напою, автомат працює далі
            //в іншому випадку адмін приходить щоб виключити апарат
            cust = counter + 1;
            cout << "Client " << cust << " has come" << endl;
            cout << "What's his budget?: ";
            cin >> sum;
            budgets.push_back(sum);//додавання суми до вектора бюджету клієнтів
            clients.push_back(cust);//додавання клієнта до вектора клієнтів
            clients[counter].setMoney(budgets[counter]);//назначаємо цю суму бюджетом клієнта
            e = 0;//обнуляємо значення куплених напоїв 
            c = 0;
            a = 0;
            l = 0;
            cycle = true;
            clients[counter].enterMoney(&coffeeMachine.cash);//клієнт вводить гроші в автомат(використовуючи клас Касова система)
            while (cycle == true) {
                if (coffeeMachine.cook.getCup() > 0) {//перевірка наявності стаканчиків
                    cout << "-Your current balance: " << coffeeMachine.cash.getBalance() << "$" << endl;//виведення на екран поточного баланса
                    cout << "-Choose your drink: " << endl;
                    cout << "1.Espresso - " << espresso.getPrice() << "$" << endl;//виведення цін за напої
                    cout << "2.Cocoa - " << cocoa.getPrice() << "$" << endl;
                    cout << "3.Americano - " << americano.getPrice() << "$" << endl;
                    cout << "4.Latte - " << latte.getPrice() << "$" << endl;
                    cout << "5.Exit" << endl;
                    cin >> drink;
                    switch (drink) {//клієнт обирає напій(або якщо він закінчив, то може вийти)
                    case 1:
                        if (espresso.getPortion() > 0) {//якщо ще є порції еспресо
                            if (clients[counter].chooseBvr(&coffeeMachine, &coffeeMachine.cash, &espresso) == false) {//йде порівняння балансу та ціни за напій
                                cout << "-Do you want to enter more money?(y/n): ";//якщо на балансі не вистачає грошей
                                cin >> agree;
                                while (agree != "y" and agree != "n") {
                                    cout << "-Please, type only 'y' or 'n': ";
                                    cin >> agree;
                                }
                                if (agree == "y") {//клієнт може або ввести ще гроші
                                    cout << "Client's budget: " << clients[counter].budget() << "$" << endl;//бюджет клієнта оновиться
                                    clients[counter].enterMoney(&coffeeMachine.cash);//баланс теж
                                    break;
                                }
                                else {//або обрати інший напій
                                    break;
                                }
                            }
                            else {//якщо на балансі вистачає грошей для обраного напою
                                if (coffeeMachine.control.heatWater(&coffeeMachine.whs, &espresso) == true) {//йде перевірка на наявність води в автоматі
                                    coffeeMachine.control.servePaperCup(&coffeeMachine.cook, &coffeeMachine.whs, &espresso);//якщо води вистачає, починається приготування напою
                                    e++;//отримує еспресо
                                }
                                else {//якщо води не вистачає навіть на еспресо(а це мінімальна к-сть води)
                                    clients[counter].money = clients[counter].money + espresso.getPrice();//клієнту повертаються гроші за незроблений напій
                                    cout << "-Your drinks are ready:" << endl;//та підсумовується його замовлення
                                    if (e > 0) {
                                        cout << e << " espresso" << endl;
                                    }
                                    if (c > 0) {
                                        cout << c << " cocoa" << endl;
                                    }
                                    if (a > 0) {
                                        cout << a << " americano" << endl;
                                    }
                                    if (l > 0) {
                                        cout << l << " latte" << endl;
                                    }
                                    cout << "-Don't forget about the rest!" << endl;
                                    cout << "-Your rest is: " << clients[counter].getRest(&coffeeMachine, &coffeeMachine.cash) << "$" << endl;//повертається решта
                                    cout << "Client's budget: " << clients[counter].budget() << "$" << endl;
                                    cout << "Client " << cust << " has left" << endl;
                                    cout << "-------------------------------------------" << endl;
                                    cycle = false;//цикл приходу клієнтів завершається
                                    coffeeMachine.cash.income = coffeeMachine.cash.income - espresso.getPrice();
                                    break;
                                }
                            }
                        }
                        else {
                            cout << "-Espresso is over. Try another drink" << endl;//якщо закінчилися усі порції напою, клієнт може обрати інший напій
                        }
                        break;
                    case 2://все теж саме для какао
                        if (cocoa.getPortion() > 0) {
                            if (clients[counter].chooseBvr(&coffeeMachine, &coffeeMachine.cash, &cocoa) == false) {
                                cout << "-Do you want to enter more money?(y/n): ";
                                cin >> agree;
                                while (agree != "y" and agree != "n") {
                                    cout << "-Please, type only 'y' or 'n': ";
                                    cin >> agree;
                                }
                                if (agree == "y") {
                                    cout << "Client's budget: " << clients[counter].budget() << "$" << endl;
                                    clients[counter].enterMoney(&coffeeMachine.cash);
                                    break;
                                }
                                else {
                                    break;
                                }
                            }
                            else {
                                if (coffeeMachine.control.heatWater(&coffeeMachine.whs, &cocoa) == true) {
                                    coffeeMachine.control.servePaperCup(&coffeeMachine.cook, &coffeeMachine.whs, &cocoa);
                                    c++;
                                }
                                else {
                                    clients[counter].money = clients[counter].money + cocoa.getPrice();
                                    cout << "-Your drinks are ready:" << endl;
                                    if (e > 0) {
                                        cout << e << " espresso" << endl;
                                    }
                                    if (c > 0) {
                                        cout << c << " cocoa" << endl;
                                    }
                                    if (a > 0) {
                                        cout << a << " americano" << endl;
                                    }
                                    if (l > 0) {
                                        cout << l << " latte" << endl;
                                    }
                                    cout << "-Don't forget about the rest!" << endl;
                                    cout << "-Your rest is: " << clients[counter].getRest(&coffeeMachine, &coffeeMachine.cash) << "$" << endl;
                                    cout << "Client's budget: " << clients[counter].budget() << "$" << endl;
                                    cout << "Client " << cust << " has left" << endl;
                                    cout << "-------------------------------------------" << endl;
                                    cycle = false;
                                    coffeeMachine.cash.income = coffeeMachine.cash.income - cocoa.getPrice();
                                    break;
                                }
                            }
                        }
                        else {
                            cout << "-Cocoa is over. Try another drink" << endl;
                        }
                        break;
                    case 3://для амерікано
                        if (americano.getPortion() > 0) {
                            if (clients[counter].chooseBvr(&coffeeMachine, &coffeeMachine.cash, &americano) == false) {
                                cout << "-Do you want to enter more money?(y/n): ";
                                cin >> agree;
                                while (agree != "y" and agree != "n") {
                                    cout << "-Please, type only 'y' or 'n': ";
                                    cin >> agree;
                                }
                                if (agree == "y") {
                                    cout << "Client's budget: " << clients[counter].budget() << "$" << endl;
                                    clients[counter].enterMoney(&coffeeMachine.cash);
                                    break;
                                }
                                else {
                                    break;
                                }
                            }
                            else {
                                if (coffeeMachine.control.heatWater(&coffeeMachine.whs, &americano) == true) {
                                    coffeeMachine.control.servePaperCup(&coffeeMachine.cook, &coffeeMachine.whs, &americano);
                                    a++;
                                }
                                else {
                                    clients[counter].money = clients[counter].money + americano.getPrice();
                                    cout << "-Your drinks are ready:" << endl;
                                    if (e > 0) {
                                        cout << e << " espresso" << endl;
                                    }
                                    if (c > 0) {
                                        cout << c << " cocoa" << endl;
                                    }
                                    if (a > 0) {
                                        cout << a << " americano" << endl;
                                    }
                                    if (l > 0) {
                                        cout << l << " latte" << endl;
                                    }
                                    cout << "-Don't forget about the rest!" << endl;
                                    cout << "-Your rest is: " << clients[counter].getRest(&coffeeMachine, &coffeeMachine.cash) << "$" << endl;
                                    cout << "Client's budget: " << clients[counter].budget() << "$" << endl;
                                    cout << "Client " << cust << " has left" << endl;
                                    cout << "-------------------------------------------" << endl;
                                    cycle = false;
                                    coffeeMachine.cash.income = coffeeMachine.cash.income - americano.getPrice();
                                    break;
                                }
                            }
                        }
                        else {
                            cout << "-Americano is over. Try another drink" << endl;
                        }
                        break;
                    case 4://для латте
                        if (latte.getPortion() > 0) {
                            if (clients[counter].chooseBvr(&coffeeMachine, &coffeeMachine.cash, &latte) == false) {
                                cout << "-Do you want to enter more money?(y/n): ";
                                cin >> agree;
                                while (agree != "y" and agree != "n") {
                                    cout << "-Please, type only 'y' or 'n': ";
                                    cin >> agree;
                                }
                                if (agree == "y") {
                                    cout << "Client's budget: " << clients[counter].budget() << "$" << endl;
                                    clients[counter].enterMoney(&coffeeMachine.cash);
                                    break;
                                }
                                else {
                                    break;
                                }
                            }
                            else {
                                if (coffeeMachine.control.heatWater(&coffeeMachine.whs, &latte) == true) {
                                    coffeeMachine.control.servePaperCup(&coffeeMachine.cook, &coffeeMachine.whs, &latte);
                                    l++;
                                }
                                else {
                                    clients[counter].money = clients[counter].money + latte.getPrice();
                                    cout << "-Your drinks are ready:" << endl;
                                    if (e > 0) {
                                        cout << e << " espresso" << endl;
                                    }
                                    if (c > 0) {
                                        cout << c << " cocoa" << endl;
                                    }
                                    if (a > 0) {
                                        cout << a << " americano" << endl;
                                    }
                                    if (l > 0) {
                                        cout << l << " latte" << endl;
                                    }
                                    cout << "-Don't forget about the rest!" << endl;
                                    cout << "-Your rest is: " << clients[counter].getRest(&coffeeMachine, &coffeeMachine.cash) << "$" << endl;
                                    cout << "Client's budget: " << clients[counter].budget() << "$" << endl;
                                    cout << "Client " << cust << " has left" << endl;
                                    cout << "-------------------------------------------" << endl;
                                    cycle = false;
                                    coffeeMachine.cash.income = coffeeMachine.cash.income - latte.getPrice();
                                    break;
                                }
                            }
                        }
                        else {
                            cout << "-Latte is over. Try another drink" << endl;
                        }
                        break;
                    case 5://завершити замовлення
                        cout << "-Your drinks are ready:" << endl;//підсумовування замовлення
                        if (e > 0) {
                            cout << e << " espresso" << endl;
                        }
                        if (c > 0) {
                            cout << c << " cocoa" << endl;
                        }
                        if (a > 0) {
                            cout << a << " americano" << endl;
                        }
                        if (l > 0) {
                            cout << l << " latte" << endl;
                        }
                        cout << "-Don't forget about the rest!" << endl;
                        cout << "-Your rest is: " << clients[counter].getRest(&coffeeMachine, &coffeeMachine.cash) << "$" << endl;//повернення решти
                        cout << "Client's budget: " << clients[counter].budget() << "$" << endl;
                        cout << "Client " << cust << " has left" << endl;
                        cout << "-------------------------------------------" << endl;
                        cycle = false;//завершення циклу для клієнта
                        break;
                    default:
                        cout << "-Wrong input. Try again" << endl;
                        break;
                    }
                }
                else {//ситуація, коли закінчилися стаканчики
                    cout << "*There are not enough paper cups in the coffee machine*" << endl;
                    cout << "-Your drinks are ready:" << endl;
                    if (e > 0) {
                        cout << e << " espresso" << endl;
                    }
                    if (c > 0) {
                        cout << c << " cocoa" << endl;
                    }
                    if (a > 0) {
                        cout << a << " americano" << endl;
                    }
                    if (l > 0) {
                        cout << l << " latte" << endl;
                    }
                    cout << "-Don't forget about the rest!" << endl;
                    cout << "-Your rest is: " << clients[counter].getRest(&coffeeMachine, &coffeeMachine.cash) << "$" << endl;
                    cout << "Client's budget: " << clients[counter].budget() << "$" << endl;
                    cout << "Client " << cust << " has left" << endl;
                    cout << "-------------------------------------------" << endl;
                    cycle = false;
                }
            }
            counter++;//збільшуємо лічильник клієнтів, бо попередній клієнт вже пішов
        }
        admin.getMoney(&coffeeMachine.cash);//адмін забирає свій доход
        cout << "Admin took the money" << endl;
        admin.turn_off(& coffeeMachine.energy);//потім вимикає автомат
        preparations(&coffeeMachine, &admin);//та перевіряє чи потрібно поповнити запаси води/цукру/стаканчиків
        cout << "Espresso's left portion: " << espresso.getPortion() << endl;
        cout << "Cocoa's left portion: " << cocoa.getPortion() << endl;
        cout << "Americano's left portion: " << americano.getPortion() << endl;
        cout << "Latte's left portion: " << latte.getPortion() << endl;
        int choice;
        bool cycle2 = true;
        while (cycle2 == true) {//поки адмін не завершить
            cout << "What do you want to refresh?" << endl;
            cout << "1.Espresso" << endl;
            cout << "2.Cocoa" << endl;
            cout << "3.Americano" << endl;
            cout << "4.Latte" << endl;
            cout << "5.End" << endl;
            cin >> choice;
            switch (choice) {//він обирає що поповнити
            case 1:
                cout << "How many?(1 pack(6 portions) = 2$): ";
                price = 2;
                espresso.countOfPortion = espresso.countOfPortion + freshenPowders(&admin, price, portion);
                break;
            case 2:
                cout << "How many?(1 pack(6 portions) = 2$): ";
                price = 2;
                cocoa.countOfPortion = cocoa.countOfPortion + freshenPowders(&admin, price, portion);
                break;
            case 3:
                cout << "How many?(1 pack(6 portions) = 3$): ";
                price = 3;
                americano.countOfPortion = americano.countOfPortion + freshenPowders(&admin, price, portion);
                break;
            case 4:
                cout << "How many?(1 pack(6 portions) = 4$): ";
                price = 4;
                latte.countOfPortion = latte.countOfPortion + freshenPowders(&admin, price, portion);
                break;
            case 5://завершення поповнення запасів
                cycle2 = false;
                break;
            }
        }
    }
}
