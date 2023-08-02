#pragma once

class Data_Base
{
	Teacher** teachers = nullptr;
	int teachers_count = 0;
	string file_name = "all_teachers.txt";

public:

	// Write To FIle

	void write_to_file()
	{
		ofstream file(this->file_name);
		if (file.is_open())
		{
			for (size_t i = 0; i < this->teachers_count; i++)
				file << this->teachers[i]->get_all();
			file.close();
		}
		else
			throw InvalidArugmentException("Unable To Open FILE", __DATE__, __TIME__, __FILE__, __LINE__);
	}

	// Constructor

	Data_Base() {}
	Data_Base(Teacher** teachers, int teachers_count) { this->set_teachers(teachers, teachers_count); }

	// Set Method

	void set_teachers(Teacher** teachers, int teachers_count)
	{
		if (teachers != nullptr)
		{
			if (this->teachers != nullptr)
			{
				for (size_t i = 0; i < this->teachers_count; i++)
					delete this->teachers[i];
				delete[] this->teachers;
			}
			this->teachers = new Teacher * [teachers_count];
			for (size_t i = 0; i < teachers_count; i++)
				this->teachers[i] = teachers[i];
			this->teachers_count = teachers_count;
		}
		else
			throw InvalidArugmentException("Invalid Parametr", __DATE__, __TIME__, __FILE__, __LINE__);
		this->write_to_file();
	}

	// + methods

	void add_teacher(Teacher* new_teacher)
	{
		for (size_t i = 0; i < this->teachers_count; i++)
		{
			if (this->teachers[i]->get_email() == new_teacher->get_email())
				throw DataBaseException("Email Exists", __DATE__, __TIME__, __FILE__, __LINE__);
			else if (this->teachers[i]->get_password() == new_teacher->get_password())
				throw InvalidArugmentException("Password Exists", __DATE__, __TIME__, __FILE__, __LINE__);
		}
		Teacher** new_teachers = new Teacher * [this->teachers_count + 1];
		for (size_t i = 0; i < this->teachers_count; i++)
			new_teachers[i] = this->teachers[i];
		new_teachers[this->teachers_count] = new_teacher;
		this->teachers_count++;
		delete[] this->teachers;
		this->teachers = new_teachers;
		this->write_to_file();
	}

	void delete_teacher(string email)
	{
		bool check = true;
		for (size_t i = 0; i < this->teachers_count; i++)
		{
			if (this->teachers[i]->get_email() == email)
			{
				check = false;
				Teacher** new_teachers = new Teacher * [this->teachers_count - 1];
				for (size_t j = 0; j < i; j++)
					new_teachers[j] = this->teachers[j];
				for (size_t c = i; c < this->teachers_count; c++)
					new_teachers[c] = this->teachers[c + 1];
				this->teachers_count--;
				delete[] this->teachers;
				this->teachers = new_teachers;
			}
		}
		if (check)
			throw DataBaseException("Invalid Email", __DATE__, __TIME__, __FILE__, __LINE__);
		this->write_to_file();
	}

	Teacher& get_teacher_by_email(string email)
	{
		for (size_t i = 0; i < this->teachers_count; i++)
		{
			if (this->teachers[i]->get_email() == email)
				return *(this->teachers[i]);
		}
		throw DataBaseException("Invalid Email", __DATE__, __TIME__, __FILE__, __LINE__);
	}

	// friend class

	friend class Registration;

	// Get Method

	inline int get_teachers_count() const { return this->teachers_count; }
	inline string get_file_name() const { return this->file_name; }

	// Destructor

	~Data_Base()
	{
		if (this->teachers != nullptr)
		{
			for (size_t i = 0; i < this->teachers_count; i++)
				delete this->teachers[i];
			delete[] this->teachers;
		}
	}
};