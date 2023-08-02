#pragma once

class Person
{
	string name;
	string surname;
	ushort age;
	string email;
	string password;

public:

	// Constructors

	Person() {}
	Person(string name, string surname, ushort age, string email, string password)
	{
		this->set_name(name);
		this->set_surname(surname);
		this->set_age(age);
		this->set_email(email);
		this->set_password(password);
	}

	// Set Methods

	void set_name(string name)
	{
		if (name.length() >= 3 && isupper(name[0]))
			this->name = name;
		else
			throw InvalidArugmentException("Invalid Name", __DATE__, __TIME__, __FILE__, __LINE__);
	}

	void set_surname(string surname)
	{
		if (surname.length() >= 3 && isupper(surname[0]))
			this->surname = surname;
		else
			throw InvalidArugmentException("Invalid SurName", __DATE__, __TIME__, __FILE__, __LINE__);
	}

	void set_age(ushort age)
	{
		if (age > 10)
			this->age = age;
		else
			throw InvalidArugmentException("Invalid Age", __DATE__, __TIME__, __FILE__, __LINE__);
	}

	void set_email(string email)
	{
		if (email.length() >= 8)
			this->email = email;
		else
			throw InvalidArugmentException("Invalid Email", __DATE__, __TIME__, __FILE__, __LINE__);
	}

	void set_password(string password)
	{
		if (password.length() >= 8)
			this->password = password;
		else
			throw InvalidArugmentException("Invalid Password", __DATE__, __TIME__, __FILE__, __LINE__);
	}

	// Get Methods

	inline string get_name() const { return this->name; }
	inline string get_surname() const { return this->surname; }
	inline ushort get_age() const { return this->age; }
	inline string get_email() const { return this->email; }
	inline string get_password() const { return this->password; }

	// Show

	virtual void show() const
	{
		cout << "Name: " << this->name << endl;
		cout << "Surname: " << this->surname << endl;
		cout << "Age: " << this->age << endl;
		cout << "Email: " << this->email << endl;
		cout << "Password: ";
		for (size_t i = 0; i < this->password.length(); i++)
			cout << "*";
		cout << endl;
	}

	// Return all

	virtual inline string get_all() const { return (this->name + " " + this->surname + " " + to_string(this->age) + " " + this->email + " " + this->password); }

	// Pure Virtual

	virtual ~Person() = 0 {}
};

class Student : public Person
{
	string Group;
	float avg;

public:

	// Constructors

	Student() : Person() {}
	Student(string name, string surname, ushort age, string email, string password, string Group, float avg) : Person(name, surname, age, email, password)
	{
		this->Group = Group;
		this->set_avg(avg);
	}

	// Set Methods

	void set_avg(float avg)
	{
		if (avg >= 0 && avg <= 12)
			this->avg = avg;
		else
			throw InvalidArugmentException("Invalid Avarage", __DATE__, __TIME__, __FILE__, __LINE__);
	}

	// Show

	void show() const override
	{
		Person::show();
		cout << "Group: " << this->Group << endl;
		cout << "Avarage: " << this->avg << endl;
	}

	// Return All

	inline string get_all() const override { return Person::get_all() + " " + to_string(this->avg) + " " + this->Group + "\n"; }

	// Get Methods

	inline string get_group() const { return this->Group; }
	inline float get_avg() const { return this->avg; }
};

class Teacher : public Person
{
	float salary;
	Student** students;
	int student_count;
	string file_name_for_students;

public:

	// Constuctors

	Teacher(string name, string surname, ushort age, string email, string password, float salary, Student** students, int student_count) : Person(name, surname, age, email, password)
	{
		salary > 0 ? this->salary = salary : throw InvalidArugmentException("Invalid Salary", __DATE__, __TIME__, __FILE__, __LINE__);
		this->file_name_for_students = this->get_email() + ".txt";
		this->set_students(students, student_count);
	}


	// Get Methods

	inline float get_salary() const { return this->salary; }

	// Set Method

	void set_students(Student** students, int student_count)
	{
		if (this->students != nullptr)
		{
			for (size_t i = 0; i < this->student_count; i++)
				delete this->students[i];
			delete[] students;
		}
		this->students = new Student * [student_count];
		for (size_t i = 0; i < student_count; i++)
			this->students[i] = new Student(students[i]->get_name(), students[i]->get_surname(), students[i]->get_age(), students[i]->get_email(), students[i]->get_password(), students[i]->get_group(), students[i]->get_avg());
		for (size_t i = 0; i < student_count; i++)
			delete students[i];
		delete[] students;
		this->student_count = student_count;
		int count = 0;
		Student** students_file = new Student * [count];
		string name_file, surname_file, email_file, password_file, group_file; ushort age_file; float avarage_file;
		ifstream file(this->get_file_name_for_students());
		if (file.is_open())
		{
			do
			{
				file >> name_file;
				if (!file.eof())
				{
					file >> surname_file;
					file >> age_file;
					file >> email_file;
					file >> password_file;
					file >> avarage_file;
					getline(file, group_file);

					Student* new_student = new Student(name_file, surname_file, age_file, email_file, password_file, group_file, avarage_file);
					Student** new_students = new Student * [count + 1];
					for (size_t i = 0; i < count; i++)
						new_students[i] = students_file[i];
					new_students[count] = new_student;
					count++;
					delete[] students_file;
					students_file = new_students;
				}

			} while (!file.eof() && name_file.length() >= 1);
		}
		file.close();
		this->students = students_file;
		this->student_count = count;
	}

	// + methods for students

	void add_student(Student* new_student)
	{
		for (size_t i = 0; i < this->student_count; i++)
		{
			if (this->students[i]->get_email() == new_student->get_email())
			{
				delete new_student;
				throw DataBaseException("Email Exists", __DATE__, __TIME__, __FILE__, __LINE__);
			}
			if (this->students[i]->get_password() == new_student->get_password())
			{
				delete new_student;
				throw DataBaseException("Password Exists", __DATE__, __TIME__, __FILE__, __LINE__);
			}
		}
		Student** new_students = new Student * [this->student_count + 1];
		for (size_t i = 0; i < this->student_count; i++)
			new_students[i] = this->students[i];
		new_students[this->student_count] = new_student;
		this->student_count++;
		delete[] this->students;
		this->students = new_students;
	}

	void delete_student(string email)
	{
		int index = -1;
		for (size_t i = 0; i < this->student_count; i++)
		{
			if (this->students[i]->get_email() == email)
			{
				index = i;
				break;
			}
		}
		if (index == -1)
			throw DataBaseException("Email Does Not Match", __DATE__, __TIME__, __FILE__, __LINE__);
		Student** new_students = new Student * [this->student_count - 1];
		for (size_t i = 0; i < index; i++)
			new_students[i] = this->students[i];
		for (size_t i = index; i < this->student_count; i++)
			new_students[i] = this->students[i + 1];
		this->student_count--;
		delete[] this->students;
		this->students = new_students;
	}

	Student* get_student_by_email(string email)
	{
		for (size_t i = 0; i < this->student_count; i++)
		{
			if (this->students[i]->get_email() == email)
			{
				break;
				return this->students[i];
			}
		}
		throw DataBaseException("Email Does Not exist", __DATE__, __TIME__, __FILE__, __LINE__);
	}

	// Save

	void save()
	{
		ofstream file(this->file_name_for_students);
		if (file.is_open())
		{
			for (size_t i = 0; i < this->student_count; i++)
				file << this->students[i]->get_all();
			file.close();
		}
		else
			throw InvalidArugmentException("Can Not Open FILE", __DATE__, __TIME__, __FILE__, __LINE__);
	}

	// Show

	void show() const
	{
		Person::show();
		cout << "Salary: " << this->salary << endl;
		cout << "Student count: " << this->student_count << endl;
	}

	// Show Only Students

	void show_students() const
	{
		if (this->student_count == 0)
			cout << "There Is Not Any Students Yet";
		for (size_t i = 0; i < this->student_count; i++)
		{
			cout << i + 1 << ")" << endl;
			this->students[i]->show();
			cout << endl;
		}
	}

	// Show Same Group Students

	void show_same_group_students(string group) const
	{
		if (this->student_count == 0)
			cout << "There Is Not Any Students Yet";
		bool check = true;
		for (size_t i = 0; i < this->student_count; i++)
		{
			if (this->students[i]->get_group() == group)
			{
				check = false;
				this->students[i]->show();
				cout << endl;
			}
		}
		if (check)
			cout << "Group Does Not Exist";
	}

	// Get Methods

	inline Student** get_students() const { return this->students; }
	inline string get_file_name_for_students() const { return this->file_name_for_students; }

	// Get All

	inline string get_all() const override { return Person::get_all() + " " + to_string(this->salary) + "\n"; }

	// destructor

	~Teacher()
	{
		if (this->students != nullptr)
		{
			for (size_t i = 0; i < this->student_count; i++)
				delete this->students[i];
			delete[] this->students;
		}
	}
};