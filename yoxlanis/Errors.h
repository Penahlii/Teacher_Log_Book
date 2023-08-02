#pragma once

class MyException : public exception
{
	string text;
	string date;
	string time;
	string source;
	int line;

public:

	MyException(const string text = "NULL Exception", const string date = "NULL", const string time = "NULL", const string source = "NULL", int line = 0)
		: exception(text.c_str())
	{
		this->date = date;
		this->time = time;
		this->source = source;
		this->line = line;

		this->text = "Text: " + string(exception::what())
			+ "\nFIle: " + this->source
			+ "\nDate: " + this->date
			+ "\nTime: " + this->time
			+ "\nLine: " + to_string(this->line);
	}

	const char* what() const override
	{
		return this->text.c_str();
	}
};

class DataBaseException : public MyException
{
public:

	DataBaseException(const string text, const string date, const string time, const string source, int line)
		: MyException(text, date, time, source, line) {}
};

class InvalidArugmentException : public MyException
{
public:

	InvalidArugmentException(const string text, const string date, const string time, const string source, int line)
		: MyException(text, date, time, source, line) {}
};