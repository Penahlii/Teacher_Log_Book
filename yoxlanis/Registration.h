#pragma once

class Registration
{
	Data_Base* data_base;

public:

	Registration(Data_Base* data_base) { this->data_base = data_base; }

	// Sign in

	Teacher* sign_in(string email, string password)
	{
		bool check_email = true;
		for (size_t i = 0; i < this->data_base->get_teachers_count(); i++)
		{
			if (this->data_base->teachers[i]->get_email() == email)
			{
				check_email = false;
				if (this->data_base->teachers[i]->get_password() == password)
					return this->data_base->teachers[i];
			}
		}
		if (check_email)
			throw DataBaseException("Email Does not Exist", __DATE__, __TIME__, __FILE__, __LINE__);
		throw DataBaseException("Password Is Not Correct", __DATE__, __TIME__, __FILE__, __LINE__);
	}

	// Sign Up

	void sign_up(Teacher* new_teacher) { this->data_base->add_teacher(new_teacher); }

	// Destructor

	~Registration() { delete this->data_base; }
};