#include <iostream>
using namespace std;

class Patient{
private:
    string name, condition;
    int age, priority;
public:
    Patient(){};
    Patient(string Name, int Age, int Priority){
        name=Name;
        age=Age;
        priority=Priority;
        if(priority==1) condition="Normal";
        else if(priority==2) condition="Urgent";
        else if(priority==3) condition="Critical";
    }
    string getName() const{
        return name;
    }
    string getCondition(){
        return condition;
    }
    int getAge() const{
        return age;
    }
    int getPriority() const{
        return priority;
    }
    void setPriority(int pr){
        priority=pr;
    }
    void setCondition(string con){
        condition=con;
    }

};

struct node
{
    int priority;
    Patient info;
    struct node *link;
};

class PriorityQueue
{
private:
    node *front;
public:
    PriorityQueue()
    {
        front= nullptr;
    }

    void insert(Patient item, int priority) {
        node *tmp, *q;
        tmp = new node;
        tmp->info = item;
        tmp->priority = priority;

        if (front == NULL || priority > front->priority) {

            tmp->link = front;
            front = tmp;
        } else {
            q = front;
            while (q->link != NULL && q->link->priority >= priority) {
                q = q->link;
            }
            tmp->link = q->link;
            q->link = tmp;
        }
        cout << "Patient " << item.getName() << " added to the queue" << endl;
    }

    void del()
    {
        node *tmp;
        if(front == NULL)
            cout<<"Queue Underflow\n";
        else
        {
            tmp = front;
            cout<<"Deleted Patient is: "<<tmp->info.getName()<<endl;
            front = front->link;
        }
    }

    void display()
    {
        node *ptr;
        ptr = front;
        if (front == NULL)
            cout<<"queue is empty"<<endl;
        else
        {
            cout<<"current patients in the queue:"<<endl;
            while(ptr != NULL)
            {
                cout<<"Name: "<<ptr->info.getName()<<", Age: "<<ptr->info.getAge()<<", Condition: "<<ptr->info.getCondition()<<", Priority: "<<ptr->info.getPriority()<<endl;
                ptr = ptr->link;
            }
        }
    }
    node* getFront() const {
        return front;
    }
    void setFront(node *newFront) {
        front = newFront;
    }
    int getSize() {
        int count = 0;
        node *ptr = front;
        while (ptr != nullptr) {
            count++;
            ptr = ptr->link;
        }
        return count;
    }
    node* findPatient(const Patient& P) {
        node *ptr = front;
        while (ptr != nullptr) {
            if (ptr->info.getName() == P.getName() && ptr->info.getAge() == P.getAge() && ptr->info.getPriority() == P.getPriority()) {
                return ptr;
            }
            ptr = ptr->link;
        }
        return nullptr;
    }
};

void addPatient(Patient P, PriorityQueue &Q){
    Q.insert(P,P.getPriority());
}

void processPatient(PriorityQueue &Q){
    Q.del();
}

void updatePatient(Patient P, PriorityQueue &Q, int newPriority) {
    node *ptr = Q.findPatient(P);
    if (ptr != nullptr) {
        ptr->info.setPriority(newPriority);
        if (newPriority == 1) ptr->info.setCondition("Normal");
        else if (newPriority == 2) ptr->info.setCondition("Urgent");
        else if (newPriority == 3) ptr->info.setCondition("Critical");
        cout << "Priority/condition of patient " << P.getName() << " updated to: " << ptr->info.getCondition() << endl;
    } else {
        cout << "Patient not found in the queue" << endl;
    }
}

void display(PriorityQueue Q){
    Q.display();
}
void getSize(PriorityQueue Q){
    cout<<"Size of the queue= "<<Q.getSize()<<endl;
}
void frontName(PriorityQueue Q){
    cout<<"front patient name: "<<Q.getFront()->info.getName()<<endl;
}
////////////////////////////////////////
#include <iostream>
#include<list>
#include<fstream>
#include<sstream>
#include<string>
using namespace std;

struct Variable{
    string name;
    string datatype;
    string value;
};

class stackOfVariables{
public:
    list<Variable> stack;
    void push(Variable& val){
        stack.push_back(val);
    }
    void pop(){
        stack.pop_back();
    }
    bool isempty(){
        return stack.empty();
    }

    void display() {
        cout << "stack : " << endl;
        for (auto it = stack.rbegin(); it != stack.rend(); ++it) {
            const auto& var = *it;
            if (var.datatype == "char") {
                cout << "name: " << var.name <<","<< " type: " << var.datatype <<","<< " value: " << var.value << endl;
            } else {
                cout << "name: " << var.name <<","<< " type: " << var.datatype <<","<< " value: " << var.value << endl;
            }
        }
        cout << endl;
    }

    bool check(string str){
        string s="";
        for(char c: str ){
            if(c== ' ') break;
            s+= c;
        }
        if (s == "int" || s == "double" || s == "char" || s == "float")    return true;
        return false;
    }


    void processLine(string line, stackOfVariables& st) {
        Variable v;
        string val;
        string datatype;
        string name;
        int idx=0;
        while(line[idx]!=' '&&line[idx]!=';'&&line[idx]!='='){
            datatype+=line[idx];
            idx++;
        }
        idx+=1;
        while(line[idx]!='='&&line[idx]!=';'&&line[idx]!='='){
            name+=line[idx];
            idx++;
        }
        idx+=1;
        while(line[idx]!=';'&&line[idx]!=';'&&line[idx]!='='){
            val+=line[idx];
            idx++;
        }
        idx+=1;



        if (check (datatype)) {
            // Declaration line
            v.name = name;
            v.value = val;
            v.datatype = datatype;
            st.push(v);
            st.display();
        }
        else {

            // Assignment line
            //cout<<datatype<<endl;
            for (auto it= st.stack.begin(); it!= st.stack.end(); it++ ) {
                if (it->name == datatype) {
                    it->value = name;
                    //st.push(*it);
                    break;
                }
            }
            st.display();
        }
    }

    void processfile(const string& filename) //to open the file
    {
        ifstream input(filename);
        string line;
        stackOfVariables s;
        while(getline(input,line))
        {
            if (line == "int main()" ||line=="{"||line=="}"){ // to avoid any other string
                continue;
            }
            if(line == "return 0;") //to stop
            {
                cout<<"reached return 0\n";
                s.display();
                while(!s.isempty())
                {
                    s.pop();
                }

                break;
            }
            processLine(line,s); // to call the function in the  loop to read each line

        }
        input.close();
    }
};



int main() {
    cout << "choose task 1 or 2: ";
    int choice;
    cin >> choice;
    switch (choice) {

        case 1: {
            cout << "Task 1:" << endl;
            PriorityQueue myQueue;
            int condition = 100;
            while (condition != 0) {
                cout << "Choose one of the options:" << endl;
                cout << "1- Add patient" << endl;
                cout << "2- Display" << endl;
                cout << "3- Update patient" << endl;
                cout << "4- Process patient" << endl;
                cout << "5- Get front name" << endl;
                cout << "6- Get size" << endl;
                cout << "0- Exit" << endl;
                cin >> condition;
                if (condition == 1) {
                    string name;
                    int age;
                    int priority;
                    cout << "Enter the name and age and priority of patient" << endl;
                    cin >> name >> age >> priority;
                    Patient p(name, age, priority);
                    addPatient(p, myQueue);
                }
                if (condition == 2) {
                    myQueue.display();
                }
                if (condition == 3) {
                    cout << "Enter name and age and priority of patient you want to update: " << endl;
                    string name;
                    int age;
                    int priority;
                    cin >> name >> age >> priority;
                    Patient p(name, age, priority);
                    cout << "Enter the new priority: ";
                    int newPriority;
                    cin >> newPriority;
                    updatePatient(p, myQueue, newPriority);
                }
                if (condition == 4) {
                    processPatient(myQueue);
                }
                if (condition == 5) {
                    frontName(myQueue);
                }
                if (condition == 6) {
                    getSize(myQueue);
                }

            }
            return 0;
        }
        case 2:{
            cout<<"task 2"<<endl;
            stackOfVariables stack;
            stack.processfile("code.txt");
            return 0;
        }
    }
}