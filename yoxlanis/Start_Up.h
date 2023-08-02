#pragma once

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

void menu_print(char** arr, int a, int size)
{
	for (size_t i = 0; i < size; i++)
	{
		if (i == a)
			SetConsoleTextAttribute(console, 10);
		else
			SetConsoleTextAttribute(console, 7);

		cout << arr[i] << endl;
	}
}

class StartUp
{
public:

	static void start()
	{

		Data_Base* data_base_of_teachers = new Data_Base;

		int count = 0;
		Teacher** teachers = new Teacher * [count];
		string name_file, surname_file, email_file, password_file; ushort age_file; float salary_file;
		ifstream file(data_base_of_teachers->get_file_name());
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
					file >> salary_file;

					int count = 0;
					Student** students = new Student * [count];
					string name_file_st, surname_file_st, email_file_st, password_file_st, group_file_st; ushort age_file_st; float avarage_file_st;
					ifstream file_st(email_file);
					if (file_st.is_open())
					{
						do
						{
							file_st >> name_file_st;
							if (!file.eof())
							{
								file_st >> surname_file_st;
								file_st >> age_file_st;
								file_st >> email_file_st;
								file_st >> password_file_st;
								file_st >> avarage_file_st;
								getline(file_st, group_file_st);

								Student* new_student = new Student(name_file_st, surname_file_st, age_file_st, email_file_st, password_file_st, group_file_st, avarage_file_st);
								Student** new_students = new Student * [count + 1];
								for (size_t i = 0; i < count; i++)
									new_students[i] = students[i];
								new_students[count] = new_student;
								count++;
								delete[] students;
								students = new_students;
							}

						} while (!file_st.eof() && name_file_st.length() >= 1);
					}
					file_st.close();

					Teacher* new_teacher = new Teacher(name_file, surname_file, age_file, email_file, password_file, salary_file, students, count);
					data_base_of_teachers->add_teacher(new_teacher);
				}
			} while (!file.eof() && name_file.length() >= 1);
		}
		file.close();
		Registration teachers_log_book(data_base_of_teachers);

		char** mymenu = new char* [3];

		mymenu[0] = new char[] {"  Sign In"};
		mymenu[1] = new char[] {"  Sign Up"};
		mymenu[2] = new char[] {"  Exit"};

		int input;
		int a = 0, b = 0;
		while (true)
		{
			system("cls");

			mymenu[a][b] = '>';


			menu_print(mymenu, a, 3);
			input = _getch();
			if (input == 224)
			{
				input = _getch();
				if (int(input) == 72)
				{
					if (a == 0)
					{
						mymenu[a][b] = ' ';
						a = 2;
					}
					else
					{
						a--;
						mymenu[a + 1][b] = ' ';
					}

				}
				else if (int(input) == 80)
				{

					if (a == 2)
					{
						mymenu[a][b] = ' ';
						a = 0;
					}
					else
					{
						a++;
						mymenu[a - 1][b] = ' ';
					}
				}

				if (a == -1 && int(input) == 72)
				{
					a = 0;
					mymenu[a][b] = ' ';
					a = 2;
				}
				if (a == 3 && int(input) == 80)
				{
					a = 2;
					mymenu[a][b] = ' ';
					a = 0;
				}
			}
			else if (input == 87)
			{
				if (a == 0)
				{
					mymenu[a][b] = ' ';
					a = 2;
				}
				else
				{
					a--;
					mymenu[a + 1][b] = ' ';
				}
			}
			else if (input == 83)
			{
				if (a == 2)
				{
					mymenu[a][b] = ' ';
					a = 0;
				}
				else
				{
					a++;
					mymenu[a - 1][b] = ' ';
				}
			}
			else if (input == '\r')
			{
				if (a == 0)
				{
					system("cls");
					string email, password;
					cout << "Enter Email: ";
					cin >> email;
					cout << "Enter Password: ";
					cin >> password;
					Teacher* current_teacher = nullptr;
					try
					{
						system("cls");
						current_teacher = teachers_log_book.sign_in(email, password);
					}
					catch (exception& ex)
					{
						if (current_teacher != nullptr)
							delete current_teacher;
						cout << ex.what();
						Sleep(3000);
						continue;
					}

					int count = 0;
					Student** students = new Student * [count];
					string name_file, surname_file, email_file, password_file, group_file; ushort age_file; float avarage_file;
					ifstream file(current_teacher->get_file_name_for_students());
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
									new_students[i] = students[i];
								new_students[count] = new_student;
								count++;
								delete[] students;
								students = new_students;
							}

						} while (!file.eof() && name_file.length() >= 1);
					}
					file.close();

					char** mymenu = new char* [7];

					mymenu[0] = new char[] {"  Show All Students "};
					mymenu[1] = new char[] {"  Show Same Group Students "};
					mymenu[2] = new char[] {"  Create Student "};
					mymenu[3] = new char[] {"  Delete Student "};
					mymenu[4] = new char[] {"  Save "};
					mymenu[5] = new char[] {"  DELETE this TEACHER Account "};
					mymenu[6] = new char[] {"  Exit "};

					int input;
					int a = 0, b = 0;
					while (true)
					{
						system("cls");

						mymenu[a][b] = '>';

						menu_print(mymenu, a, 7);
						input = _getch();
						if (input == 224)
						{
							input = _getch();
							if (int(input) == 72)
							{
								if (a == 0)
								{
									mymenu[a][b] = ' ';
									a = 6;
								}
								else
								{
									a--;
									mymenu[a + 1][b] = ' ';
								}

							}
							else if (int(input) == 80)
							{

								if (a == 6)
								{
									mymenu[a][b] = ' ';
									a = 0;
								}
								else
								{
									a++;
									mymenu[a - 1][b] = ' ';
								}
							}
							if (a == -1 && int(input) == 72)
							{
								a = 0;
								mymenu[a][b] = ' ';
								a = 6;
							}
							if (a == 7 && int(input) == 80)
							{
								a = 6;
								mymenu[a][b] = ' ';
								a = 0;
							}
						}
						else if (input == 87)
						{
							if (a == 0)
							{
								mymenu[a][b] = ' ';
								a = 6;
							}
							else
							{
								a--;
								mymenu[a + 1][b] = ' ';
							}
						}
						else if (input == 83)
						{
							if (a == 6)
							{
								mymenu[a][b] = ' ';
								a = 0;
							}
							else
							{
								a++;
								mymenu[a - 1][b] = ' ';
							}
						}
						else if (input == '\r')
						{
							if (a == 0)
							{
								system("cls");
								current_teacher->show_students();
								Sleep(7000);
								system("cls");
							}
							else if (a == 1)
							{
								system("cls");
								string group;
								cout << "Enter Group: ";
								cin >> group;
								system("cls");
								current_teacher->show_same_group_students(group);
								Sleep(5000);
							}
							else if (a == 2)
							{
								system("cls");
								string name, surname, email, password, group; ushort age; float avarage;
								cout << "Enter Name: ";
								cin >> name;
								cout << "Enter Surname: ";
								cin >> surname;
								cout << "Enter Age: ";
								cin >> age;
								cout << "Enter Email: ";
								cin >> email;
								cout << "Enter Password: ";
								cin >> password;
								cout << "Enter Group: ";
								cin >> group;
								cout << "Enter Avarage: ";
								cin >> avarage;

								try
								{
									system("cls");
									Student* new_student = new Student(name, surname, age, email, password, group, avarage);
									current_teacher->add_student(new_student);
									cout << "New Student Added succesfully";
									Sleep(3000);
								}
								catch (exception& ex)
								{
									cout << ex.what() << endl;
									Sleep(5000);
								}
							}
							else if (a == 3)
							{
								system("cls");
								string email;
								cout << "Enter Student's email: ";
								cin >> email;
								system("cls");
								try
								{
									current_teacher->delete_student(email);
									cout << "Student Deleted Succesfully";
									Sleep(3000);
								}
								catch (exception& ex)
								{
									cout << ex.what();
									Sleep(5000);
								}
							}
							else if (a == 4)
							{
								system("cls");
								try
								{
									current_teacher->save();
									cout << "All Saved Succesfully";
									Sleep(3000);
								}
								catch (exception& ex)
								{
									cout << ex.what();
									Sleep(5000);
								}
							}
							else if (a == 5)
							{
								system("cls");
								string password;
								cout << "Enter Your Account's password: ";
								cin >> password;
								if (password == current_teacher->get_password())
									data_base_of_teachers->delete_teacher(current_teacher->get_email());
								else
								{
									cout << "Invalid Password";
									Sleep(2000);
								}
							}
							else if (a == 6)
								break;
						}
					}
				}
				else if (a == 1)
				{
					SetConsoleTextAttribute(console, 7);
					system("cls");
					string name;
					string surname;
					ushort age;
					string email;
					string password;
					float salary;

					cout << "Enter Name: ";
					cin >> name;
					cout << "Enter Surname: ";
					cin >> surname;
					cout << "Enter Age: ";
					cin >> age;
					cout << "Enter Email: ";
					cin >> email;
					cout << "Enter Password: ";
					cin >> password;
					cout << "Enter Salary: ";
					cin >> salary;

					system("cls");

					try
					{
						Teacher* new_teacher = new Teacher(name, surname, age, email, password, salary, nullptr, 0);
						data_base_of_teachers->add_teacher(new_teacher);
						cout << "Teacher Added Succesfully";
						Sleep(3000);
					}
					catch (exception& ex)
					{
						cout << ex.what();
						Sleep(5000);
					}
				}
				else if (a == 2)
				{
					system("cls");
					SetConsoleTextAttribute(console, 7);
					cout << "Good-Bye!!";
					break;
				}
			}
		}
	}
};