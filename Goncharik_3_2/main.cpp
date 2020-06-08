#include <iostream>
#include <conio.h>
#include <math.h>
#include <iomanip>
#include <list>
#include <string>
#include <vector>

using namespace std;

void print_indent(int count)
{
	for (int i = 0; i < count; i++)
	{
		cout << " ";
	}
}

// ласс одной оценки
class Mark
{
	double mark_;
public:

	Mark()
	{
	}

	Mark(double mark)
	{
		mark_ = mark;
	}

	double get_mark()
	{
		return mark_;
	}
};

//оценки по предмету дл¤ одной группы
class SubjectResults
{
	string subject_;
	list<Mark*> results_;
public:

	SubjectResults()
	{
	}

	SubjectResults(string& subject)
	{
		subject_ = subject;
	}

	string get_name()
	{
		return subject_;
	}

	Mark* get(int index)
	{
		if (index < 0) return nullptr;
		if (index >= results_.size()) return nullptr;

		auto iter = results_.begin();
		for (int i = 0; i < index; index++)
		{
			iter++;
		}

		return *iter;
	}

	void add(Mark* mark)
	{
		results_.emplace_back(mark);
	}

	void insert(Mark* mark, int index)
	{
		if (index < 0) return;
		if (index >= results_.size()) return;

		auto iter = results_.begin();
		for (int i = 0; i < index; index++)
		{
			iter++;
		}
		results_.insert(iter, mark);
	}

	double average()
	{
		double sum = 0;
		int count = 0;
		for (auto iter = results_.begin(); iter != results_.end(); iter++, count++)
		{
			sum += (*iter)->get_mark();
		}
		return sum / count;
	}

	void analyze(int indent)
	{
		print_indent(indent);
		cout << get_name() << "\n";
		for (auto iter = results_.begin(); iter != results_.end(); iter++)
		{
			print_indent(indent + 1);
			cout << (*iter)->get_mark() << " ";
		}
		cout << "\n";
		print_indent(indent);
		cout << "Subject Average: " << average() << "\n";
	}
};

//список результатов по предметам в одной группе
class GroupResults
{
	string group_name_;
	list<SubjectResults*> results_;
public:

	GroupResults()
	{
	}

	GroupResults(string& name)
	{
		group_name_ = name;
	}

	string get_name()
	{
		return group_name_;
	}

	SubjectResults* get(int index)
	{
		if (index < 0) return nullptr;
		if (index >= results_.size()) return nullptr;

		auto iter = results_.begin();
		for (int i = 0; i < index; index++)
		{
			iter++;
		}

		return *iter;
	}

	void add(SubjectResults* results)
	{
		results_.emplace_back(results);
	}

	void insert(SubjectResults* results, int index)
	{
		if (index < 0) return;
		if (index >= results_.size()) return;

		auto iter = results_.begin();
		for (int i = 0; i < index; index++)
		{
			iter++;
		}
		results_.insert(iter, results);
	}

	int get_subjects_count()
	{
		return results_.size();
	}

	double average()
	{
		double sum = 0;
		int count = 0;
		for (auto iter = results_.begin(); iter != results_.end(); iter++, count++)
		{
			sum += (*iter)->average();
		}
		return sum / count;
	}

	double* get_subjects_averages()
	{
		auto subjects_averages = new double[results_.size()]{0};
		int index = 0;
		for (auto iter = results_.begin(); iter != results_.end(); iter++, index++)
		{
			subjects_averages[index] = (*iter)->average();
		}
		return subjects_averages;
	}

	void analyze(int indent)
	{
		print_indent(indent);
		cout << get_name() << "\n";
		for (auto iter = results_.begin(); iter != results_.end(); iter++)
		{
			(*iter)->analyze(indent + 1);
		}
		print_indent(indent);
		cout << "Group Average: " << average() << "\n";
	}
};

//список результатов групп в факультете
class FacultyResults
{
	string faculty_name_;
	list<GroupResults*> results_;

public:

	FacultyResults()
	{
	}

	FacultyResults(string& name)
	{
		faculty_name_ = name;
	}

	string get_name()
	{
		return faculty_name_;
	}

	GroupResults* get(int index)
	{
		if (index < 0) return nullptr;
		if (index >= results_.size()) return nullptr;

		auto iter = results_.begin();
		for (int i = 0; i < index; index++)
		{
			iter++;
		}

		return *iter;
	}

	void add(GroupResults* results)
	{
		results_.emplace_back(results);
	}

	void insert(GroupResults* results, int index)
	{
		if (index < 0) return;
		if (index >= results_.size()) return;

		auto iter = results_.begin();
		for (int i = 0; i < index; index++)
		{
			iter++;
		}
		results_.insert(iter, results);
	}

	double average()
	{
		double sum = 0;
		int count = 0;
		for (auto iter = results_.begin(); iter != results_.end(); iter++, count++)
		{
			sum += (*iter)->average();
		}
		return sum / count;
	}

	double* find_subjects_averages()
	{
		if (results_.size() == 0) return nullptr;
		auto averages = new double[(*results_.begin())->get_subjects_count()]{0};
		int index = 0;
		for (auto iter = results_.begin(); iter != results_.end(); iter++, index++)
		{
			auto subject_averages = (*iter)->get_subjects_averages();
			for (int i = 0; i < index; i++)
			{
				averages[i] += subject_averages[i];
			}
			delete[] subject_averages;
		}
		return averages;
	}

	void analyze(int indent)
	{
		print_indent(indent);
		cout << get_name() << "\n";
		for (auto iter = results_.begin(); iter != results_.end(); iter++)
		{
			(*iter)->analyze(indent + 1);
		}
		print_indent(indent);
		cout << "Faculty Average: " << average() << "\n";
		print_indent(indent);
		cout << "Faculty per Subject Averages: \n";
		auto subject_averages = find_subjects_averages();
		print_indent(indent);
		if (subject_averages == nullptr)
		{
			cout << "Unknown";
		}
		else
		{
			for (int i = 0; i < (*results_.begin())->get_subjects_count(); i++)
			{
				cout << subject_averages[i] << " ";
			}
		}
		cout << "\n";
	}
};

class University
{
	string university_name_;
	list<FacultyResults*> results_;
public:

	University()
	{
	}

	University(string& name)
	{
		university_name_ = name;
	}

	string get_name()
	{
		return university_name_;
	}

	FacultyResults* get(int index)
	{
		if (index < 0) return nullptr;
		if (index >= results_.size()) return nullptr;

		auto iter = results_.begin();
		for (int i = 0; i < index; index++)
		{
			iter++;
		}

		return *iter;
	}

	void add(FacultyResults* results)
	{
		results_.emplace_back(results);
	}

	void insert(FacultyResults* results, int index)
	{
		if (index < 0) return;
		if (index >= results_.size()) return;

		auto iter = results_.begin();
		for (int i = 0; i < index; index++)
		{
			iter++;
		}
		results_.insert(iter, results);
	}

	double average()
	{
		double sum = 0;
		int count = 0;
		for (auto iter = results_.begin(); iter != results_.end(); iter++, count++)
		{
			sum += (*iter)->average();
		}
		return sum / count;
	}

	void analyze()
	{
		print_indent(0);
		cout << get_name() << "\n";
		for (auto iter = results_.begin(); iter != results_.end(); iter++)
		{
			(*iter)->analyze(0 + 1);
		}
	}
};

University* randomize(int faculties_count, int groups_count, int subjects_count, int students_count)
{
	string university_name = "University!";
	auto university = new University(university_name);

	for (int f = 0; f < faculties_count; ++f)
	{
		string faculty_name = "Faculty: " + to_string(f);
		auto faculty_results = new FacultyResults(faculty_name);
		for (int g = 0; g < groups_count; g++)
		{
			string group_name = "Group: " + to_string(g);
			auto group_results = new GroupResults(group_name);
			for (int sub = 0; sub < subjects_count; ++sub)
			{
				string subject_name = "Subject: " + to_string(sub);
				auto subject_results = new SubjectResults(subject_name);
				for (int stud = 0; stud < students_count; ++stud)
				{
					double mark = rand() % 20 / 10. + 3; // от 3 до 5 с шагом 0.1
					subject_results->add(new Mark(mark));
				}
				group_results->add(subject_results);
			}
			faculty_results->add(group_results);
		}
		university->add(faculty_results);
	}

	return university;
}

int main()
{
	setlocale(LC_ALL, "russian");
	//сгенерировать 3 факультета, с 5 группами в каждом, так чтобы было 3 предмета дл¤ 10 студентов
	auto university = randomize(3, 5, 3, 10);
	university->analyze();
	delete university;
	system("pause");
	return 0;
}
