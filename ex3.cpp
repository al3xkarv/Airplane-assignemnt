#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <ctime>

using namespace std;

int OBJECT_ID=0;

//Forward Declaration
class String;
class PlaneComponent;



class Object{
    protected:
        int id;

    public:
        Object(){
            id=++OBJECT_ID;
            cout << " Object [" << id << "] created." << endl;
        }



        Object(int id){
            this->id=id;
            cout << " Object [" << id << "] created." << endl;
        }


        int getId(){
            return id;
        }

        //checks if 2 objects are equal
        bool equal(Object* obj){
            if (obj->id==getId()){
                return true;
            }
            return false;
        }



        //checkes if 2 objects are the same object
        bool identical(Object* obj){

            if (obj==this){
                return true;
            }
            return false;
        }


        virtual Object*  clone() = 0;

        //makes all members of class a string and concats them
        virtual String toString() =0;

        virtual ~Object(){
            cout << " Object [" << id << "] destroyed." << endl;
        }

    };

class String : public Object{
    protected:
        std::string text;
    public:
        String(std::string input){
            text=input;
            cout << " String [" << id << "]created." << endl;
        }

        //constructor used for clone()
        String(std::string input, int newId){
            text = input;
            id = newId;
            cout << " String [" << id <<"]created." << endl;
        }

        std::string getText(){
            return text;
        }

        int length (){
            return text.length();
        }

        void clear(){
            text.clear();
        }

        String concat(String input){
            String str(text + input.getText());
            return str;
        }

        char at(int index){
            return text.at(index);
        }

        void updateAt(int index, char letter){
            text[index] = letter;
        }

        void print(){
            cout<< text << endl;
        }

        //creates new object with same values and return pointer  to the new object
        String*  clone()
        {
            String* String_pointer = new String(text, id);
            return String_pointer;
        }

        //checks if 2 objects are equal
        bool equal(String* str){
            if (str->id==getId() && str->text == text){
                return true;
            }
            return false;
        }



        //checkes if 2 objects are the same object
        bool identical(String* str){

            if (str==this){
                return true;
            }
            return false;
        }

        String toString(){
            std::string str ="String with id " + std::to_string(id);
            String str1(str);
            return str1;
        }

        ~String(){
        cout << " String [" << id << "]destroyed." << endl;
        }

    };


class Employee: public Object{
    protected:
        String* name;
    public:
        Employee(){
            cout << "Employee ["<< id <<  "] created." << endl;
        }

        String* getName(){
            return name;
        }
        virtual void workOn(PlaneComponent* component) = 0;

        virtual void report(PlaneComponent* component) = 0;

        virtual~Employee(){
            cout << "Employee [" << id<< "] destroyed." << endl;
        }

};


class PlaneComponent: public Object{
    protected:
        bool securityCheck;
    public:
        PlaneComponent(){
        securityCheck = false;
        cout << " PlaneComponent [" <<id<< "]created." << endl;
        }

        bool getSecurityCheck (){
            return securityCheck;
        }

        virtual void setMaintainance(bool value) = 0;

        virtual void setCleaning(bool value) = 0;

        virtual void setSecurity(bool value) = 0;

        virtual bool ready_check() = 0;

        virtual void process(Employee* e) = 0;


        virtual ~PlaneComponent(){
            cout << " PlaneComponent [" <<id<< "]destroyed." << endl;
        }
    };

class PassengerCompartment : public PlaneComponent {
    private:
        PassengerCompartment* insideCompartment = NULL;
        bool cleaningCheck;
    public:
        PassengerCompartment(){
            cleaningCheck = false;
            insideCompartment = new PassengerCompartment(true);
            cout << " PassengerCompartment [" <<id<<  "]created." << endl;
        }

        PassengerCompartment(bool withoutInsideCompartment){
            cleaningCheck = false;
            cout << " PassengerCompartment [" << id <<  "]created." << endl;
        }

        PassengerCompartment(int clonedId, bool cleaning, bool security){
            cleaningCheck = cleaning;
            securityCheck = security;
            id = clonedId;
            cout << " Cloned PassengerCompartment [" << id <<  "]created." << endl;
        }

        bool getCleaningCheck(){
            return cleaningCheck;
        }

        PassengerCompartment* getInsideCompartment(){
            return insideCompartment;
        }

         void setSecurity(bool value){
            securityCheck = value;
        }

        void setMaintainance(bool value){}

        void setCleaning(bool value){
            cleaningCheck = value;
        }

        bool ready_check(){
            if (cleaningCheck && securityCheck){
                cout<< " Passenger Compartment OK!" <<endl;
                return true;
            }
            else {
                cout<<" Passenger Compartment not ready.." << endl;
                return false;
            }
        }

        void process(Employee* e){
            e->workOn(this);
            if (insideCompartment!=NULL){
                insideCompartment->process(e);
            }
        }

        //creates new object with same values and return pointer  to the new object
        PassengerCompartment*  clone(){

            PassengerCompartment* cloneCompartment = new PassengerCompartment(id, getCleaningCheck(), getSecurityCheck());
            return cloneCompartment;
        }

        //checks if 2 objects are equal
        bool equal(PassengerCompartment* cmp){
            if (cmp->getId()==id && cmp->getCleaningCheck() == cleaningCheck && cmp->getSecurityCheck() == securityCheck){
                if (insideCompartment !=NULL && cmp->getInsideCompartment()!=NULL){

                    if (insideCompartment->getId() == cmp->getInsideCompartment()->getId() && insideCompartment->getCleaningCheck() == cmp->getInsideCompartment()->getCleaningCheck() && insideCompartment->getSecurityCheck() == cmp->getInsideCompartment()->getSecurityCheck()){
                        return true;
                    }
                    else{
                        return false;
                    }
                }
                else if(insideCompartment !=NULL || cmp->getInsideCompartment()!=NULL){
                    return false;
                }
                return true;
            }
            return false;
        }



        //checkes if 2 objects are the same object
        bool identical(PassengerCompartment* cmp){

            if (cmp==this){
                return true;
            }
            return false;
        }


        String toString() {
            std::string str1 = "PassengerCompartment with id = ";
            str1 = str1 + std::to_string(id);
            // std::string str1 = std::to_string(id);
            str1 = str1 +" securityCheck = " ;
            if (securityCheck == true){
                str1 = str1 + " true";
            }
            else{
                str1 = str1 + " false";
            }
            str1 = str1 + " cleaningCheck ";
            if (cleaningCheck == true){
                str1 = str1 + "true ";
            }
            else{
                str1 = str1 + " false ";
            }
            String str(str1);
            if (insideCompartment != NULL){
                return str.concat(insideCompartment->toString()) ;
            }
            return str;


        }

        ~PassengerCompartment(){
            if (insideCompartment!=NULL){
            delete insideCompartment;
            }
            cout << " PassengerCompartment ["<< id <<   "]destroyed." << endl;
        }


};

class PrivateCompartment : public PlaneComponent {
    protected:
        bool cleaningCheck;
        bool maintainanceCheck;
    public:
        PrivateCompartment(){
            cleaningCheck = false;
            maintainanceCheck = false;
            cout << " PrivateCompartment [" <<id <<   "]created." << endl;
        }

        PrivateCompartment(int clonedId, bool cleaning, bool security, bool maintainance){
            cleaningCheck = cleaning;
            securityCheck = security;
            maintainanceCheck = maintainance;
            id = clonedId;
            cout << " Cloned PrivateCompartment ["   "]created." << endl;
        }


        void setSecurity(bool value)
        {
            securityCheck = value;
        }

        void setMaintainance(bool value){
            maintainanceCheck = value;
        }

        void setCleaning(bool value){
            cleaningCheck = value;
        }

        bool getCleaningCheck(){
            return cleaningCheck;
        }

        bool getMaintainanceCheck(){
                return maintainanceCheck;
        }

        bool ready_check() {
            if (cleaningCheck && getSecurityCheck()){
                cout<< " Private Compartment OK!" <<endl;
                return true;
            }
            else {
                cout<<" Private Compartment not ready.." << endl;
                return false;
            }
        }


        void process(Employee* e){
            e->workOn(this);
        }



        PrivateCompartment*  clone() {
            PrivateCompartment* cloneCompartment = new PrivateCompartment(id, getCleaningCheck(), getSecurityCheck(), getMaintainanceCheck());
            return cloneCompartment;
        }

        //checks if 2 objects are equal
        bool equal(PrivateCompartment* cmp){
            if (cmp->getId()==id && cmp->getCleaningCheck() == cleaningCheck  && cmp->getSecurityCheck() == securityCheck && cmp->getMaintainanceCheck() == maintainanceCheck){
                return true;
            }
            return false;
        }



        //checkes if 2 objects are the same object
        bool identical(PrivateCompartment* cmp){

            if (cmp==this){
                return true;
            }
            return false;
        }

        String toString() {
            std::string str1 = " Private Compartment with id = ";
            str1 = str1 + std::to_string(id);
            // std::string str1 = std::to_string(id);
            str1 = str1 +" securityCheck = " ;
            if (securityCheck == true){
                str1 = str1 + " true ";
            }
            else{
                str1 = str1 + " false ";
            }
            str1 = str1 + " cleaningCheck ";
            if (cleaningCheck == true){
                str1 = str1 + " true ";
            }
            else{
                str1 = str1 + " false ";
            }
            if (maintainanceCheck == true){
                str1 = str1 +" true ";
            }
            else {
                str1 = str1 + " false ";
            }
            String str(str1);

            return str;
        }

        ~PrivateCompartment(){
            cout << " PrivateCompartment [" << id <<   "]destroyed. " << endl;
        }


};

class EquipmentCompartment : public PrivateCompartment{

    public:
        EquipmentCompartment(){
            cout << " EquipmentCompartment [" << id <<  "]created. " << endl;
        }
        EquipmentCompartment(int cloneId, bool security, bool maintainance){
            id = cloneId;
            securityCheck = security;
            maintainanceCheck = maintainance;
            cout << " EquipmentCompartment [" << id <<  "]created. " << endl;
        }

        EquipmentCompartment(EquipmentCompartment* equipIn){
            id = equipIn->getId();
            securityCheck = equipIn -> getSecurityCheck();
            maintainanceCheck = equipIn -> getMaintainanceCheck();
        }


        bool ready_check(){
            if (maintainanceCheck && getSecurityCheck()){
                cout<< " Equipment Compartment OK!" <<endl;
                return true;
            }
            else {
                cout<<" Equipment Compartment not ready.." << endl;
                return false;
            }
        }

        void process(Employee* e){
            e->workOn(this);
            // securityCheck=true;
        }

        EquipmentCompartment*  clone(){
            EquipmentCompartment* cloneCompartment = new EquipmentCompartment(id, getSecurityCheck(), getMaintainanceCheck());
            return  cloneCompartment;
            }

        //checks if 2 objects are equal
        bool equal(EquipmentCompartment* cmp){
            if (cmp->getId()==id && cmp->getCleaningCheck() == cleaningCheck  && cmp->getSecurityCheck() == securityCheck && cmp->getMaintainanceCheck() == maintainanceCheck){
                return true;
            }
            return false;
        }



        //checkes if 2 objects are the same object
        bool identical(EquipmentCompartment* cmp){

            if (cmp==this){
                return true;
            }
            return false;
        }

        String toString() {
            std::string str1 = " EquipmentCompartment with id = ";
            str1 = str1 + std::to_string(id);
            str1 = str1 +" securityCheck = " ;
            if (securityCheck == true){
                str1 = str1 + " true ";
            }
            else{
                str1 = str1 + " false ";
            }
            str1 = str1 + " cleaningCheck = ";
            if (cleaningCheck == true){
                str1 = str1 + " true ";
            }
            else{
                str1 = str1 + " false ";
            }
            str1 = str1 + " maintainanceCheck = " ;
            if (maintainanceCheck == true){
                str1 = str1 +" true ";
            }
            else {
                str1 = str1 + " false ";
            }
            String str(str1);

            return str;}


        ~EquipmentCompartment(){

            cout << " EquipmentCompartment [" <<id<<  "]destroyed. " << endl;
        }
};

class CargoBay : public PrivateCompartment{
    private:
        EquipmentCompartment* cargoEquipment;
    public:
        CargoBay(){
            securityCheck = false;
            maintainanceCheck = false;
            cleaningCheck = false;
            cargoEquipment = new EquipmentCompartment();
            cout << " CargoBay [" <<id<<  "]created. " << endl;
        }

        CargoBay(int cloneId, bool security, bool maintainance, bool cleaning, EquipmentCompartment* equipIn){
            id = cloneId;
            maintainanceCheck = maintainance;
            cleaningCheck = cleaning;
            securityCheck = security;
            cargoEquipment = new EquipmentCompartment(equipIn);
            cout << " CargoBay [" <<id<<  "]created. " << endl;
        }

        EquipmentCompartment* getCargoEquipmnet(){
            return cargoEquipment;
        }

        bool ready_check(){
            if (getMaintainanceCheck() && getCleaningCheck() && getSecurityCheck()){
                cout<< " Private Compartment OK! " <<endl;
                return true;
            }
            else {
                cout<<" Private Compartment not ready.. " << endl;
                return false;
            }
        }


        void process(Employee* e){
            e->workOn(this);
            cargoEquipment->process(e);

        }


        CargoBay*  clone(){

            CargoBay* cloneCargo = new CargoBay(id, getSecurityCheck(), getMaintainanceCheck(), getCleaningCheck(), cargoEquipment);

            return cloneCargo;
        }

        //checks if 2 objects are equal
        bool equal(CargoBay* crg){
            if (crg->getId()==id && crg->getCleaningCheck() == cleaningCheck && crg->getSecurityCheck() == securityCheck && crg->getMaintainanceCheck() == maintainanceCheck && cargoEquipment->equal(crg->getCargoEquipmnet())){
                    return true;
                }
            return false;
        }



        //checkes if 2 objects are the same object
        bool identical(CargoBay* crg){

            if (crg==this){
                return true;
            }
            return false;
        }

        String toString() {
            std::string str1 = " CargoBay with id = ";
            str1 = str1 + std::to_string(id);
            str1 = str1 +" securityCheck = " ;
            if (securityCheck == true){
                str1 = str1 + " true ";
            }
            else{
                str1 = str1 + " false ";
            }
            str1 = str1 + " cleaningCheck ";
            if (cleaningCheck == true){
                str1 = str1 + " true ";
            }
            else{
                str1 = str1 + " false ";
            }
            str1 = str1 + " maintainanceCheck ";
            if (maintainanceCheck == true){
                str1 = str1 +" true ";
            }
            else {
                str1 = str1 + " false";
            }
            String str(str1);
            return str.concat(cargoEquipment->toString());
        }

        ~CargoBay(){
            delete cargoEquipment;
            cout << " CargoBay [" <<id<<  "]destroyed." << endl;
        }
};

class Plane: public Object{
    private:
        //not sure if String* is good
        String* title;
        int passengerCapacity;
        CargoBay* cargo;
        EquipmentCompartment* equipmentComp1;
        EquipmentCompartment* equipmentComp2;
        EquipmentCompartment* equipmentComp3;
        std::vector<PassengerCompartment*> passengersCompartments;
        // std::vector<PlaneComponent> PlaneComponents;
    public:
        Plane(){
            title = new String("Boeing");
            cargo = new CargoBay();
            equipmentComp1 = new EquipmentCompartment();
            equipmentComp2 = new EquipmentCompartment();
            equipmentComp3 = new EquipmentCompartment();
            passengerCapacity = rand() % 300;
            int numberOfPassengerCompartments = passengerCapacity/50 +1;
            passengersCompartments.resize(numberOfPassengerCompartments);
            for (int i = 0; i < numberOfPassengerCompartments; i++) {
                passengersCompartments[i] = new PassengerCompartment();
            }
            // passengersCompartments
            cout << " Plane [" <<id<< "] created." << endl;
        }
        //clonedPlane
        Plane(int clonedId, String* clonedTitle, int capacity, CargoBay* cargoIn, EquipmentCompartment* comp1, EquipmentCompartment* comp2 ,EquipmentCompartment* comp3, std::vector<PassengerCompartment*> compartments ){
            id = clonedId;
            title = clonedTitle;
            passengerCapacity = capacity;
            cargo = cargoIn;
            equipmentComp1 = comp1;
            equipmentComp2 = comp2;
            equipmentComp3 = comp3;
            passengersCompartments.resize(compartments.size());
            for (unsigned i = 0; i < compartments.size(); i++) {
                passengersCompartments[i] = compartments [i];
            }
            cout << " Cloned Plane [" <<id<< "] created." << endl;
        }

        String* getTitle(){
            return title;
        }

        int getPassengerCapacity(){
            return passengerCapacity;
        }

        CargoBay* getCargoBay(){
            return cargo;
        }

        EquipmentCompartment* getEquipmentComp1(){
            return equipmentComp1;
        }

        EquipmentCompartment* getEquipmentComp2(){
            return equipmentComp2;
        }

        EquipmentCompartment* getEquipmentComp3(){
            return equipmentComp3;
        }

        std::vector<PassengerCompartment*> getPassengersCompartments(){
            return passengersCompartments;
        }

        Plane*  clone() {
            String* titleIn;
            EquipmentCompartment* clonedEquipmentComp1;
            EquipmentCompartment* clonedEquipmentComp2;
            EquipmentCompartment* clonedEquipmentComp3;
            CargoBay* clonedCargo;
            std::vector<PassengerCompartment*> clonedPassengersCompartments;
            titleIn = title->clone();
            clonedEquipmentComp1 = equipmentComp1->clone();
            clonedEquipmentComp2 = equipmentComp2->clone();
            clonedEquipmentComp3 = equipmentComp3->clone();
            clonedCargo = cargo->clone();
            clonedPassengersCompartments.resize(passengersCompartments.size());
            for (unsigned i = 0; i < passengersCompartments.size(); i++) {
                clonedPassengersCompartments[i] = passengersCompartments[i]->clone();
            }
            Plane* clonedPlane = new Plane(id, titleIn, passengerCapacity, clonedCargo, clonedEquipmentComp1, clonedEquipmentComp2, clonedEquipmentComp3, clonedPassengersCompartments );
            return clonedPlane;
        }

        //checks if 2 objects are equal
        bool equal(Plane* pln){

            if (pln->getId()==id && title->equal(pln->getTitle())  && pln->getPassengerCapacity() == passengerCapacity && cargo->equal(pln->getCargoBay())){
                //separation for visibility
                if (equipmentComp1->equal(pln->getEquipmentComp1()) && equipmentComp2->equal(pln->getEquipmentComp2()) && equipmentComp3->equal(pln->getEquipmentComp3()) && passengersCompartments.size() == pln->getPassengersCompartments().size() )
                    for (unsigned i = 0; i < passengersCompartments.size(); i++) {
                        if (passengersCompartments[i]->equal(pln->getPassengersCompartments()[i]) == false ) {
                            return false;
                        }
                    }
                return true;
                }
            return false;
        }

        //checkes if 2 objects are the same object
        bool identical(Plane* pln){

            if (pln==this){
                return true;
            }
            return false;
        }

        bool ready_check(){
            if (equipmentComp1->ready_check() && equipmentComp2->ready_check() && equipmentComp1->ready_check() && cargo->ready_check()){
                for (unsigned i = 0; i < passengersCompartments.size(); i++) {
                    if (passengersCompartments[i]->ready_check() == false ) {
                        return false;
                    }
                }
                return true;
            }
            return false;
        }

        String toString(){
            std::string str1 = "Plane with id = ";
            str1 = str1 + std::to_string(id);
            str1 = str1 + " name: Boeing  passengerCapacity =" + std::to_string(passengerCapacity) + " and" ;
            String str2(str1);
            String str(str1);
            str2 = str.concat(cargo->toString());
            str = str2;
            str2 = str.concat(equipmentComp1->toString());
            str = str2;
            str2 = str.concat(equipmentComp2->toString());
            str = str2;
            str2 = str.concat(equipmentComp3->toString());
            str = str2;
            for (unsigned i = 0; i < passengersCompartments.size(); i++) {
                str2 = str.concat(passengersCompartments[i]->toString());
                str = str2;
                // clonedPassengersCompartments[i] = passengersCompartments[i]->clone();
            }
            return str2;
        }

        void process(Employee* e){
            String str = e->toString();
            str.print();
            cargo->process(e);
            equipmentComp1->process(e);
            equipmentComp2->process(e);
            equipmentComp3->process(e);
            for (unsigned i = 0; i < passengersCompartments.size(); i++) {
                passengersCompartments[i]->process(e);
            }
        }

        ~Plane(){
            delete title;
            delete cargo;
            delete equipmentComp1;
            delete equipmentComp2;
            delete equipmentComp3;
            // for (unsigned i=0 ; i<passengersCompartments.size(); i++) {
            //     PassengerCompartment* it = passengersCompartments.at(i);
            for (vector<PassengerCompartment*>::iterator it = passengersCompartments.begin(); it != passengersCompartments.end(); ++it)
            {
                PassengerCompartment* a = *it;
              delete a;
              a = NULL;
            }
            passengersCompartments.clear();
            cout << " Plane [" <<id<< "] destroyed." << endl;
        }
};


class SecurityEmployee : public Employee {
    public:
        SecurityEmployee(){
            name = new String(" Default Defaultidis");
            cout<< "SecurityEmployee [ " << id <<" ] created"<< endl;
        }

        SecurityEmployee(int clonedId, String* clonedName){
            name = clonedName->clone();
            cout<< "SecurityEmployee [ " << id <<" ] created"<< endl;
        }

        void workOn(PlaneComponent* component){
            component->setSecurity(true);
            report(component);
        }

        void report(PlaneComponent* component){
            cout<< "SecurityEmployee working on : " ;
            String str = component->toString();
            str.print();
        }

        SecurityEmployee*  clone(){

            SecurityEmployee* clonedMaintainance = new SecurityEmployee(id, name);
            return clonedMaintainance;
        }

        //checks if 2 objects are equal
        bool equal(SecurityEmployee* se){
            if (se->getId()==id && se->getName()->equal(name) ){
                    return true;
                }
            return false;
        }

        //checkes if 2 objects are the same object
        bool identical(SecurityEmployee* se){

            if (se == this){
                return true;
            }
            return false;
        }

        String toString() {
            std::string str1 = " SecurityEmployee [";
            str1 = str1 + std::to_string(id);
            str1 = str1 +  "] with id = ";
            String str(str1);
            // str = str.concat(*name);
            return str.concat(*name);
        }

        ~SecurityEmployee(){
            delete name;
            cout<<"SecurityEmployee [ "<< id <<"] destroyed" <<endl;
        }
    };

class MaintainanceEmployee : public Employee {
    public:
        MaintainanceEmployee(){
            name = new String(" Default Defaultidis");
            cout<< "MaintainanceEmployee [" << id << "[ created"<< endl;
        }

        MaintainanceEmployee(int clonedId, String* clonedName){
            name = clonedName->clone();
            cout<< "MaintainanceEmployee [ " << id <<" ] created"<< endl;
        }

        void workOn(PlaneComponent* component){
            component->setMaintainance(true);
            component->toString();
            report(component);
        }

        void report(PlaneComponent* component){
            cout<< "MaintainanceEmployee working on: ";
            String str = component->toString();
            str.print();
        }

        MaintainanceEmployee*  clone(){

            MaintainanceEmployee* clonedSecurity = new MaintainanceEmployee(id, name);
            return clonedSecurity;
        }

        //checks if 2 objects are equal
        bool equal(MaintainanceEmployee* me){
            if (me->getId()==id && me->getName()->equal(name) ){
                    return true;
                }
            return false;
        }

        //checkes if 2 objects are the same object
        bool identical(MaintainanceEmployee* me){
            if (me == this){
                return true;
            }
            return false;
        }

        String toString() {
            std::string str1 = " MaintainanceEmployee with id = ";
            str1 = str1 + std::to_string(id);

            String str(str1);
            // str = str.concat(*name);
            return str.concat(*name);
        }

        ~MaintainanceEmployee(){
            delete name;
            cout<<"MaintainanceEmployee [" << id << " destroyed" <<endl;
        }
    };

class CleaningEmployee : public Employee {
    public:
        CleaningEmployee(){
            name = new String(" Default Defaultidis");
            cout<< "CleaningEmployee [" << id << " created"<< endl;
        }

        CleaningEmployee(int clonedId, String* clonedName){
            name = clonedName->clone();
            cout<< "CleaningEmployee [ " << id <<" ] created"<< endl;
        }

        void workOn(PlaneComponent* component){
            component->setCleaning(true);
            report(component);
        }

        void report(PlaneComponent* component){
            cout<< "CleaningEmployee working on :";
            String str = component->toString();
            str.print();
        }

        CleaningEmployee*  clone(){

            CleaningEmployee* clonedCleaning = new CleaningEmployee(id, name);
            return clonedCleaning;
        }

        //checks if 2 objects are equal
        bool equal(SecurityEmployee* ce){
            if (ce->getId()==id && ce->getName()->equal(name) ){
                    return true;
                }
            return false;
        }



        //checkes if 2 objects are the same object
        bool identical(CleaningEmployee* ce){

            if (ce == this){
                return true;
            }
            return false;
        }

        String toString() {
            std::string str1 = " CleaningEmployee with id = ";
            str1 = str1 + std::to_string(id);
            String str(str1);
            // str = str.concat(*name);
            return str.concat(*name);
        }


        ~CleaningEmployee(){
            delete name;
            cout<<"CleaningEmployee [" << id << "destroyed" <<endl;
        }
    };

void clone_encrypt_and_print(Object* obj){
    Object* cloned = obj->clone();
    if (cloned->equal(obj)){
        cout<<"They are equal" << endl;
    }
    else{
        cout<<"They are not equal"<<endl;
    }
    String str1 = obj->toString();
    String str2 = cloned->toString();
    for (int i = 0; i < rand() % str2.length(); i++) {
        str2.updateAt(rand() % str2.length() , str2.at(rand() % str2.length()) );
    }
    str1.print();
    str2.print();
    String str = str1.concat(str2);
    cout <<"Length of concat Strings is "<<str.length()<< endl;;
    if (str.length() % 2 == 1) {
        cout<< str.at(str.length() / 2)<< endl;;
    }
    else{
        cout<< str.at(str.length() / 2)<< endl;;
        cout<< str.at(str.length() / 2 +1)<< endl;;

    }
    str.clear();
    cout<< "Length after clear of String is " <<str.length()<<endl;
    delete cloned;
    }


int main(int argc, char *argv[])
{
    srand(time(NULL));
    Plane a3;
    SecurityEmployee se;
    CleaningEmployee ce;
    MaintainanceEmployee me;

    a3.process(&se);
    a3.process (&ce);
    a3.process (&me);
    if (a3.ready_check()) {
        cout << "Plane ready to take off!"<<endl;
    }

    clone_encrypt_and_print(&a3);

    return 0;
}
