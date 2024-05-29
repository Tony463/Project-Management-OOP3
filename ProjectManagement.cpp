#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits>
#include <exception>
#include <memory>
#include <algorithm>
#include <numeric>
#include <set>

using namespace std;


// define my custom exception
class MyException : public exception {
public:
    const char* what() const noexcept override {
        return "Value not in the required range!";
    }
};

class Resource{
protected:
    string resource_name;
    double quantity;
    double hourly_cost;
public:
    // constructor for Resource objects
    Resource(const string& resource_name_, double quantity_, double hourly_cost_):
        resource_name(resource_name_), quantity(quantity_),hourly_cost(hourly_cost_){}

    // default constructor
    Resource(){}

    // virtual destructor
    virtual ~Resource() {}

    // pure virtual function to calculate cost
    virtual double calculate_cost() const = 0;


    virtual ostream& print(ostream& os) const {
        os << "Resource Name: " << resource_name << endl;
        os << "Quantity: " << quantity << endl;
        os << "Hourly Cost: " << hourly_cost << endl;
        return os;
    }

    friend ostream& operator<<(ostream& os, const Resource& resource) {
        return resource.print(os);
    }

    virtual istream& read(istream& is) {
        cout << "Enter resource name: ";
        getline(is >> ws, resource_name);
        cout << "Enter resource quantity: ";
        is >> quantity;
        cout << "Enter resource hourly cost: ";
        is >> hourly_cost;
        return is;
    }

    friend istream& operator>>(istream& is, Resource& resource) {
        return resource.read(is);
    }


     // overload == operator for class Resource
    bool operator==(const Resource& other) const {
        return (resource_name == other.resource_name &&
                quantity == other.quantity &&
                hourly_cost == other.hourly_cost);
    }

    // getters and setters
    double get_resource_hourly_cost()
    const {
        return hourly_cost;
    }

    double get_quantity()
    const {
        return quantity;
    }
    void set_quantity(double quantity_)
    {
        quantity = quantity_;
    }
    string get_resource_name()
    const {
        return resource_name;
    }
    void set_resource_name(const string& name) {
    resource_name = name;
    }

    void set_resource_hourly_cost(double hourly_cost_) {
    hourly_cost = hourly_cost_;
    }


};

template <typename T>
class ObjectManager{
    vector<shared_ptr<T>> objects;
    set<shared_ptr<T>> objects1;
    public:
    void add_resource(const shared_ptr<T>& res)
    {
        objects.push_back(res);
        objects1.insert(res);
    }
    void delete_resource(const shared_ptr<T>& res)
    {
        auto it = find(objects.begin(), objects.end(), res);
        if(it != objects.end())
        {
            objects.erase(it);
            objects1.erase(it);
        }
    }
    void print_objects()
    {
        for(const auto& res : objects)
        {
            cout << *res << endl;
        }
    }

};

class LaborResource : public Resource {
    string role;
    int experience_years;
    int rating;
public:
    // Initialization Constructor
    LaborResource(string resource_name_, double quantity_, double hourly_cost_, string role_, int experience_years_, int rating_):
        Resource(resource_name_, quantity_, hourly_cost_), role(role_), experience_years(experience_years_), rating(rating_) {}


    // default constructor
    LaborResource(){}


    // calculate cost, override base class function
    double calculate_cost() const override {
        return quantity * hourly_cost * (rating / 10);
    }

    ostream& print(ostream& os) const override {
        Resource::print(os);
        os << "Labor Resource Role: " << get_role() << endl;
        os << "Experience Years: " << get_experience_years() << endl;
        os << "Rating: " << get_rating() << endl;
        return os;
    }

    friend ostream& operator<<(ostream& os, const LaborResource& laborresource)
    {
        return laborresource.print(os);
    }

    istream& read(istream& is) override {
        Resource::read(is); // Call base class read function
        cout << "Enter labor resource role: ";
        getline(is >> ws, role);
        cout << "Enter labor resource experience years: ";
        is >> experience_years;
        cout << "Enter labor rating: ";
        is >> rating;
        return is;
    }
    friend istream& operator>>(istream& is, LaborResource& laborresource)
    {
        return laborresource.read(is);
    }

    string get_role() const {
        return role;
    }

    void set_role(const string& role_) {
        role = role_;
    }

    int get_experience_years() const {
        return experience_years;
    }

    void set_experience_years(int years) {
        experience_years = years;
    }
    int get_rating() const{
        return rating;
    }
    void throwCustomException() const {
        throw MyException();
    }

    // Metodă pentru a arunca o excepție standard
    void throwStandardException() const {
        throw runtime_error("A standard exception occurred!");
    }
};

class SoftwareResource : public Resource {
    string type;
    string version;
    double reduction;
public:
    // Initialization Constructor
    SoftwareResource(const string& resource_name_, double quantity_, double hourly_cost_, const string& type_, const string& version_, double reduction_):
        Resource(resource_name_, quantity_, hourly_cost_), type(type_), version(version_), reduction(reduction_) {}

    // default constructor
    SoftwareResource(){}


    // calculate cost and override base class function
    double calculate_cost() const override {
        return quantity * hourly_cost * reduction;
    }


     ostream& print(ostream& os) const override {
        Resource::print(os); // Call base class print function
        os << "Software Resource Type: " << type << endl;
        os << "Version: " << version << endl;
        os << "Reduction: " << reduction << endl;
        return os;
        }

     friend ostream& operator<<(ostream& os, const SoftwareResource& softwareresource)
     {
         return softwareresource.print(os);
     }

    istream& read(istream& is) override {
        Resource::read(is); // Call base class read function
        cout << "Enter software resource type: ";
        getline(is >> ws, type);
        cout << "Enter software resource version: ";
        getline(is >> ws, version);
        cout << "Enter the reduction percentage: ";
        is >> reduction;
        return is;
        }

    friend istream& operator>>(istream& is, SoftwareResource& softwareresource)
    {
        return softwareresource.read(is);
    }

    string get_type() const {
        return type;
    }

    void set_type(const string& type_) {
        type = type_;
    }

    string get_version() const {
        return version;
    }

    void set_version(const string& version_) {
        version = version_;
    }
    double get_reduction() const {
        return reduction;
    }
};

class Task{

protected:
    string task_name;
    int priority; // range 1-3 1=low, 2=medium, 3=high
    string task_status; //in-progress, completed,delayed
    int start_date;
    int end_date;
    vector<shared_ptr<LaborResource>> labor_resources;
    vector<shared_ptr<SoftwareResource>> software_resources;
public:
    // constructor for Task objects
    Task(const string& task_name_, int priority_, const string& task_status_, int start_date_, int end_date_, const vector<shared_ptr<LaborResource>>& labor_resources_, const vector<shared_ptr<SoftwareResource>>& software_resource_):
        task_name(task_name_), priority(priority_), task_status(task_status_), start_date(start_date_), end_date(end_date_), labor_resources(labor_resources_), software_resources(software_resource_){}

    // default constructor
    Task() = default;

    // virtual destructor
    virtual ~Task() {}

    // pure virtual function for calculate cost for a task
    virtual double calculate_task_cost() const = 0;


    // methods
    double calculate_total_cost() const {

        double total_labor, total_software = 0;
        total_labor = accumulate(labor_resources.begin(), labor_resources.end(), 0.0, [](double sum, const shared_ptr<LaborResource>& labor){
            return sum + labor->calculate_cost();
        });
         total_software = accumulate(software_resources.begin(), software_resources.end(), 0.0, [](double sum, const shared_ptr<SoftwareResource>& software){
            return sum + software->calculate_cost();
        });
        return total_labor + total_software;
    }


     virtual ostream& print(ostream& os) const {
        os << "Task Name: " << task_name << endl;
        os << "Priority: " << priority << endl;
        os << "Task Status: " << task_status << endl;
        os << "Start Date: " << start_date << endl;
        os << "End Date: " << end_date << endl;

        os << "Labor Resources:" << endl;
        for (const auto& labor_res : labor_resources) {
            os << *labor_res;
        }

        os << "Software Resources:" << endl;
        for (const auto& software_res : software_resources) {
            os << *software_res;
        }

        return os;
    }


    virtual istream& read(istream& is) {
        cout << "Enter Task Name: ";
        getline(is >> ws, task_name);
        cout << "Enter Priority (1-3): ";
        is >> priority;
        cout << "Enter Task Status: ";
        getline(is >> ws, task_status);
        cout << "Enter Start Date: ";
        is >> start_date;
        cout << "Enter End Date: ";
        is >> end_date;

        cout << "Enter Labor Resources:" << endl;
        LaborResource labor_res;
        while (is >> labor_res) {
            labor_resources.push_back(make_shared<LaborResource>(labor_res));
        }
        is.clear();

        cout << "Enter Software Resources:" << endl;
        SoftwareResource software_res;
        while (is >> software_res) {
            software_resources.push_back(make_shared<SoftwareResource>(software_res));
        }
        is.clear();

        return is;
    }

    friend ostream& operator<<(ostream& os, const Task& task) {
        return task.print(os);
    }

    friend istream& operator>>(istream& is, Task& task) {
        return task.read(is);
    }


    // getters and setters
    vector<shared_ptr<LaborResource>> get_LaborResource() const {
        return labor_resources;
    }
    vector<shared_ptr<SoftwareResource>> get_SoftwareResource() const {
        return software_resources;
    }
    int get_start_date() const {
        return start_date;

    }
    int get_end_date() const {
        return end_date;
    }

};



class BugTask : public Task {
    string bug_description;
    int severity; // Number between 1 and 3

public:
    // Initialization Constructor
    BugTask(const string& task_name_, int priority_, const string& task_status_, int start_date_, int end_date_,
            const string& bug_description_, int severity_,
            const vector<shared_ptr<LaborResource>>& labor_resources_, const vector<shared_ptr<SoftwareResource>>& software_resources_) :
        Task(task_name_, priority_, task_status_, start_date_, end_date_, labor_resources_, software_resources_),
        bug_description(bug_description_), severity(severity_) {}

    // Default constructor
    BugTask() : bug_description(""), severity(0){}


    // methods
   virtual double calculate_task_cost() const override {
        double cost = Task::calculate_total_cost();
        double multiplier = 1.0;
        if (severity == 2) {
            multiplier = 1.1;
        } else if (severity == 3) {
            multiplier = 1.2;
        }
        if(severity < 1 || severity > 3)
        {
            throw MyException();
        }
        return cost * multiplier;
    }


    ostream& print(ostream& os) const override {
        Task::print(os);
        os << "Bug Description: " << bug_description << endl;
        os << "Severity: " << severity << endl;
        return os;
    }

    // Override read function
    istream& read(istream& is) override {
        Task::read(is); // Call base class read function
        cout << "Enter Bug Description: ";
        getline(is >> ws, bug_description);
        cout << "Enter Severity (1-3): ";
        is >> severity;
        return is;
    }
    friend ostream& operator<<(ostream& os, const BugTask& task) {
        return task.print(os);
    }

    friend istream& operator>>(istream& is, BugTask& task) {
        return task.read(is);
    }

    //getters and setters
    string getBugDescription() const {
        return bug_description;
    }

    int getSeverity() const {
        return severity;
    }
};





class FeatureTask : public Task {
private:
    string feature_description;
    int complexity; // 1 - low, 2 - medium, 3 - high

public:
    // Initialization Constructor
    FeatureTask(const string& task_name_, int priority_, const string& task_status_, int start_date_, int end_date_,
                const string& feature_description_, const string& customer_feedback_, int complexity_,
                const vector<shared_ptr<LaborResource>>& labor_resources_, const vector<shared_ptr<SoftwareResource>>& software_resources_) :
        Task(task_name_, priority_, task_status_, start_date_, end_date_, labor_resources_, software_resources_),
        feature_description(feature_description_), complexity(complexity_) {}

    // Override calculate_task_cost for dynamic dispatch
   virtual double calculate_task_cost() const override {
        double base_cost = Task::calculate_total_cost();
        double additional_cost = 0.0;
        if(getComplexity() < 1 || getComplexity() > 3)
        {
            throw MyException();
        }
        else
        {
             additional_cost = getComplexity() * 100;
            return base_cost + additional_cost;
        }
    }

    ostream& print(ostream& os) const override {
        Task::print(os); // Call base class print function
        os << "Feature Description: " << feature_description << endl;
        os << "Complexity: " << complexity << endl;
        return os;
    }

    // Override read function
    istream& read(istream& is) override {
        Task::read(is); // Call base class read function
        cout << "Enter Feature Description: ";
        getline(is >> ws, feature_description);
        cout << "Enter Complexity (1-3): ";
        is >> complexity;
        return is;
    }

    friend ostream& operator<<(ostream& os, const FeatureTask& task) {
        return task.print(os);
    }

    friend istream& operator>>(istream& is, FeatureTask& task) {
        return task.read(is);
    }


    // Getters for feature description, customer feedback, and complexity
    string getFeatureDescription() const {
        return feature_description;
    }


    int getComplexity() const {
        return complexity;
    }
};



class ResearchTask : public Task{
private:
    string topic;
public:

    // Initialization Constructor
    ResearchTask(const string& task_name_, int priority_, const string& task_status_, int start_date_, int end_date_,
                 const string& topic_,
                 const vector<shared_ptr<LaborResource>>& labor_resources_, const vector<shared_ptr<SoftwareResource>>& software_resources_) :
        Task(task_name_, priority_, task_status_, start_date_, end_date_, labor_resources_, software_resources_),
        topic(topic_) {}

    // Default Constructor
    ResearchTask() : Task(), topic("") {}

    // Override calculate_task_cost for dynamic dispatch
    virtual double calculate_task_cost() const override {
        double base_cost = Task::calculate_total_cost();
        int research_time = get_end_date() - get_start_date();
        double additional_daily_cost = 50;
        return base_cost + (research_time * 50);
    }


     ostream& print(ostream& os) const override {
        Task::print(os); 
        os << "Research Topic: " << topic << endl;
        return os;
    }

    // Override read function
    istream& read(istream& is) override {
        Task::read(is); 
        cout << "Enter Research Topic: ";
        getline(is >> ws, topic);
        return is;
    }
    friend ostream& operator<<(ostream& os, const ResearchTask& task) {
        return task.print(os);
    }

    friend istream& operator>>(istream& is, ResearchTask& task) {
        return task.read(is);
    }


    // getters and setters
    string get_topic() const {
        return topic;

    }
};

template <typename T>
void afis_vector(const vector<shared_ptr<T>>& vector)
{
    for(const auto& v : vector)
    {
        cout << *v;
    }
}


class Observer {
public:
    virtual void update(weak_ptr<Task> task) = 0;
};

class TaskManagement {
private:
    vector<shared_ptr<Task>> tasks;
    vector<weak_ptr<Observer>> observers;

public:
    TaskManagement() = default;

    void add_task(shared_ptr<Task> task) {
        tasks.push_back(task);
        notify_observers(task);  // Notify observers when a task is added
    }

    void attach(shared_ptr<Observer> observer) {
        observers.push_back(observer);
    }


    void notify_observers(shared_ptr<Task> task) {
        for (auto& weak_observer : observers) {
            if (auto observer = weak_observer.lock()) { // Check if the observer still exists
                observer->update(task); // Call update function on the observer
            }
        }
    }

    void total_cost() const {
        double total_cost = 0;
        for (auto& task : tasks) {
            if (task) {
                total_cost += task->calculate_task_cost();
            }
        }
        cout << "Total cost: " << total_cost << endl;
    }

    void print_tasks() const {
        afis_vector(tasks);
    }

    const vector<shared_ptr<Task>>& get_tasks() const {
        return tasks;
    }
};


class Menu {
private:
    static shared_ptr<Menu> instance;
    TaskManagement taskManagement;

    Menu() {}

public:
    static shared_ptr<Menu> get_instance() {
        if (!instance) {
            instance = shared_ptr<Menu>(new Menu());
        }
        return instance;
    }

    void display() {
        int choice;
        do {
            cout << "1. Print total cost of tasks" << endl;
            cout << "2. Print Tasks" << endl;
            cout << "3. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    taskManagement.total_cost();
                    break;
                case 2:
                    taskManagement.print_tasks();
                    break;
                case 3:
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 3);
    }

    TaskManagement& getTaskManagement() {
        return taskManagement;
    }

    void add_task(shared_ptr<Task> task) {
        taskManagement.add_task(task);
    }
};

shared_ptr<Menu> Menu::instance = nullptr;


class Display : public Observer {
public:
    void update(weak_ptr<Task> task_weak) override {
        if (auto task_shared = task_weak.lock()) { // Check if task is still valid
            cout << *task_shared << endl; 
        } else {
            cout << "Task no longer exists." << endl; // Handle the case where task has expired
        }
    }
};

int main() {
    auto menu = Menu::get_instance();

    ObjectManager<LaborResource> laborManager;

    auto display1 = make_shared<Display>();

    TaskManagement& taskManagement = menu->getTaskManagement();
    taskManagement.attach(display1);

    LaborResource labor1("John Doe", 1.0, 50.0, "Developer", 5, 8);
    LaborResource labor2("Jane Smith", 1.5, 60.0, "Designer", 3, 7);

    SoftwareResource software1("Software A", 2.0, 100.0, "Type A", "1.0", 0.9);
    SoftwareResource software2("Software B", 1.0, 80.0, "Type B", "2.0", 0.8);

    auto laborResource1 = make_shared<LaborResource>(labor1);
    auto laborResource2 = make_shared<LaborResource>(labor2);

    auto softwareResource1 = make_shared<SoftwareResource>(software1);
    auto softwareResource2 = make_shared<SoftwareResource>(software2);

    vector<shared_ptr<LaborResource>> laborResources1 = {laborResource1};
    vector<shared_ptr<LaborResource>> laborResources2 = {laborResource2};

    vector<shared_ptr<SoftwareResource>> softwareResources1 = {softwareResource1};
    vector<shared_ptr<SoftwareResource>> softwareResources2 = {softwareResource2};

    auto bugTask1 = make_shared<BugTask>("Bug Task 1", 3, "in-progress", 20240501, 20240515, "Description 1", 3, laborResources1, softwareResources1);
    auto bugTask2 = make_shared<BugTask>("Bug Task 2", 2, "completed", 20240510, 20240520, "Description 2", 2, laborResources2, softwareResources2);
    menu->add_task(bugTask1);
    menu->add_task(bugTask2);

    auto featureTask1 = make_shared<FeatureTask>("Feature Task 1", 2, "delayed", 20240505, 20240525, "Description 1", "Feedback 1", 3, laborResources1, softwareResources1);
    auto featureTask2 = make_shared<FeatureTask>("Feature Task 2", 1, "in-progress", 20240515, 20240610, "Description 2", "Feedback 2", 2, laborResources2, softwareResources2); // Added missing 'complexity'
    menu->add_task(featureTask1);
    menu->add_task(featureTask2);

    auto researchTask1 = make_shared<ResearchTask>("Research Task 1", 1, "completed", 20240501, 20240510, "Topic 1", laborResources1, softwareResources1);
    auto researchTask2 = make_shared<ResearchTask>("Research Task 2", 3, "in-progress", 20240515, 20240525, "Topic 2", laborResources2, softwareResources2);
    menu->add_task(researchTask1);
    menu->add_task(researchTask2);

    menu->display();

    return 0;
}



