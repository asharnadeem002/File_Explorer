#include<iostream>
#include<cstring>
#include<string>
#include<time.h>
#include<stdio.h>
#pragma warning(disable : 4996)
using namespace std;
class file{
private:
	friend class file_system;
	friend class Folder;
	string work, name, rootLink;
	date AcctimeAdate, CrtimeAdate;
public:
	file(){
		name = "xyz", work = "", rootLink = "";
		CrtimeAdate.timeAdate = CrtimeAdate.CutimeAdate(), AcctimeAdate.timeAdate = AcctimeAdate.CutimeAdate();
	}
};
class folder{
private:
	friend class file_system;
	friend folder* Gfolder(string rootPath, string& name, bool& CorPath, file_system& O, int t);
public:
	string name, rootLink;
	date CrtimeAdate, AcctimeAdate;
	int NoFiles = 0, NoSuFolds = 0, fileColSize = 0;
	file* ColFiles = nullptr;
	folder* ColFolds = nullptr;
	folder() :rootLink{ "" }, ColFiles{ new file[2] }, name{ "xyz" }, fileColSize{ 2 }, NoFiles{ 0 }, NoSuFolds{ 0 }{
		CrtimeAdate.timeAdate = CrtimeAdate.CutimeAdate(), AcctimeAdate.timeAdate = AcctimeAdate.CutimeAdate();
	}
	folder(string na){
		name = na;
	}
	~folder(){
		delete[] ColFolds, delete[] ColFiles;
	}
	folder& operator=(const folder& x){
		name = x.name, rootLink = x.rootLink, CrtimeAdate = x.CrtimeAdate, AcctimeAdate = x.AcctimeAdate, NoFiles = x.NoFiles, NoSuFolds = x.NoSuFolds, fileColSize = x.fileColSize;
		ColFiles = new file [x.NoFiles], ColFolds = new folder[x.NoSuFolds];
		for (int i = 0; i < x.fileColSize; i++)
			ColFiles[i] = x.ColFiles[i];
		for (int i = 0; i < x.NoSuFolds; i++)
			ColFolds[i] = x.ColFolds[i];
		return *this;
	}
	folder(const folder& x){
		name = x.name, rootLink = x.rootLink, CrtimeAdate = x.CrtimeAdate, AcctimeAdate = x.AcctimeAdate, NoFiles = x.NoFiles, NoSuFolds = x.NoSuFolds, fileColSize = x.fileColSize;
		ColFiles = new file[x.NoFiles], ColFolds = new folder[x.NoSuFolds];
		for (int i = 0; i < x.fileColSize; i++)
			ColFiles[i] = x.ColFiles[i];
		for (int i = 0; i < x.NoSuFolds; i++)
			ColFolds[i] = x.ColFolds[i];
	}
};
class date {
private: 
public:
	string timeAdate;
	string CutimeAdate() {
		time_t     now = time(0);
		struct tm  tstruct;
		char       buf[80];
		tstruct = *localtime(&now);
		strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
		return buf;
	}
};
class file_system{
private:
	folder base;
	friend folder* Gfolder(string rootPath, string& name, bool& CorPath, file_system& O, int t);
public:
	file_system():base{"base"}{}
	void folderMaking(string rootPath, string name){
		bool CorPath = true;
		string name1;
		folder* CuFolder = Gfolder(rootPath, name1, CorPath, *this, 0);
		if (!CorPath)
			cout << "Invalid Path! " << endl;
		else{
			folder* t = new folder[CuFolder->NoSuFolds + 1];
			for (int i = 0; i < CuFolder->NoSuFolds; ++i)
				t[i] = CuFolder->ColFolds[i];
			CuFolder->ColFolds = t;
			CuFolder->ColFolds[CuFolder->NoSuFolds].CrtimeAdate.timeAdate = CuFolder->ColFolds[CuFolder->NoSuFolds].CrtimeAdate.currentDateTime();
			CuFolder->ColFolds[CuFolder->NoSuFolds].AcctimeAdate.timeAdate = CuFolder->ColFolds[CuFolder->NoSuFolds].CrtimeAdate.currentDateTime();
			CuFolder->ColFolds[CuFolder->NoSuFolds].name = name, CuFolder->ColFolds[CuFolder->NoSuFolds].NoSuFolds = 0, CuFolder->ColFolds[CuFolder->NoSuFolds].rootLink = rootPath;
			CuFolder->ColFolds[CuFolder->NoSuFolds].ColFiles = new file[2], CuFolder->ColFolds[CuFolder->NoSuFolds].NoFiles = 2, CuFolder->ColFolds[CuFolder->NoSuFolds].fileColSize = 0, CuFolder->NoSuFolds++;
			delete[] CuFolder->ColFolds;
		}
	}
	void fileMaking(string rootPath, string name, string Work){
		bool CorPath = true;
		string name1;
		folder* CuFolder = Gfolder(rootPath, name1, CorPath, *this, 0);
		if (!CorPath)
			cout << "Invalid path! " << endl;
		else{
			if (CuFolder->fileColSize >= CuFolder->NoFiles){
				file* t = new file[CuFolder->NoFiles * 2];
				for (int i = 0; i < CuFolder->fileColSize; ++i)
					t[i] = CuFolder->ColFiles[i];
				CuFolder->NoFiles *= 2, CuFolder->ColFiles = t;
				delete[] CuFolder->ColFiles;
			}
			CuFolder->ColFiles[CuFolder->fileColSize].rootLink = rootPath, CuFolder->ColFiles[CuFolder->fileColSize].name = name, CuFolder->ColFiles[CuFolder->fileColSize].work = Work;
			CuFolder->ColFiles[CuFolder->fileColSize].CrtimeAdate.timeAdate = CuFolder->ColFiles[CuFolder->fileColSize].CrtimeAdate.CutimeAdate();
			CuFolder->ColFiles[CuFolder->fileColSize].AcctimeAdate.timeAdate = CuFolder->ColFiles[CuFolder->fileColSize].AcctimeAdate.CutimeAdate(), CuFolder->fileColSize++;
		}
	}
	void seeFile(string rootPath){
		string name;
		bool CorPath = true;
		folder* tarFolder = Gfolder(rootPath, name, CorPath, *this, 1);
		if (CorPath){
			tarFolder->AcctimeAdate.timeAdate = tarFolder->AcctimeAdate.CutimeAdate();
			for (int i = 0; i < tarFolder->fileColSize; i++)
				cout << tarFolder->ColFiles[i].work << endl, tarFolder->ColFiles[i].AcctimeAdate.timeAdate = tarFolder->ColFiles[i].AcctimeAdate.currentDateTime();
		}
		else
			cout << "Invalid path! " << endl;
	}
};
folder* Gfolder(string rootPath, string& name, bool& CorPath, file_system& O, int t){
	int idx = 0;
	for (int i = 0; rootPath[i] != '\\' && rootPath[i] != 0; i++){
		if (rootPath[i] != O.base.name[i]){
			CorPath = false;
			break;
		}
		idx = i;
	}
	idx = idx + 2;
	//idx++;
	folder* CuFolder = &O.base;
	if (CorPath){
		for (int i = idx; rootPath[i] != 0; i++){
			int count = 0;
			for (int j = i; rootPath[j] != '\\' && rootPath[j] != 0; j++)
				count++;
			char* Npath = new char[count + 1];
			bool Fpath = false;
			int no = 0;
			for (; rootPath[i] != '\\' && rootPath[i] != 0; i++){
				Npath[no] = rootPath[i];
				no++;
			}
			Npath[no] = '\0';
			bool fo = false;
			for (int k = 0; k < CuFolder->NoSuFolds; k++){
				if (t == 1 && rootPath[i] == '\0'){
					name = Npath;
					break;
				}
				if (CuFolder->ColFolds[k].name == Npath){
					CuFolder = &CuFolder->ColFolds[k];
					fo = true;
					break;
				}
			}
			if (fo == false){
				if (t == 0)
					CorPath = false;
				else if (rootPath[i] == '\0')
					CorPath = true;
			}
			if (rootPath[i] == '\0')
				break;
		}
	}
	return CuFolder;
}
int main(){
	file_system filee;
	filee.folderMaking("base//OOP//assignments","Important");
	filee.folderMaking("base//OOP//assignments", "Important1");
	filee.fileMaking("base//OOP//assignments", "important2.txt", "ashar nadeem");
	filee.fileMaking("base//OOP//assignments", "important3.txt", "ashar ashar nadeem");
	filee.seeFile("base//OOP//assignments//");
	system("pause");
	return 0;
}