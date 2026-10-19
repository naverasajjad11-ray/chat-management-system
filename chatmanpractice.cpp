#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<ctime>
using namespace std;
class Person{
	protected:
	string name;
	public:
		Person(){
			name="unknown";
		}
	Person(string n){
		name=n;
	}
	string getname(){
		return name;
	}
};
class User:public Person{
	bool online;
	public:
		User(){
			name="unknown";
		}
		User(string n):Person(n){
			online=false;
		}
		void setonline(bool status){
			online=status;
		}
		bool isonline(){
		return online;
		}
};
class Message{
	protected:
	string sender;
	string receiver;
	string time;
	string text;
	int likes;
	public:
		Message(){
			likes=0;
		}
		Message(string s,string r,string t,string ti){
			sender=s;
			receiver=r;
			time=ti;
			text=t;
			likes=0;
		}
		virtual void show(int index){
			cout<<"["<<index<<"]";
			cout<<sender<<" -> "<<receiver<<" : ";
			cout<<text;
			cout<<"[LIKES : "<<likes<<"]"<<endl;
			}
			
		
		string getsender(){
			return sender;
		}
		string getreceiver(){
			return receiver;
		}
		string gettext(){
			return text;
		}
		virtual string gettype()=0;
		string gettime(){
			return time;
		}
		int getlikes(){
			return likes;
		}
		void like(){
			likes++;
		}
		void edit(string newtext){
			text=newtext;
		}
		void setlikes(int l){
			likes=l;
		}
		virtual ~Message(){}
};
class Textmessage:public Message{
	public:
		Textmessage(string s,string r,string t,string ti){
			sender=s;
			receiver=r;
			text=t;
			time=ti;
			likes=0;
		}
		string gettype(){
			return "TEXT";
		}
};
class Imagemessage:public Message{
	public:
		Imagemessage(string s,string r,string t,string ti){
			sender=s;
			receiver=r;
			text=t;
			time=ti;
			likes=0;
		}
		void show(int index){
			cout<<"["<<index<<"]";
			cout<<sender<<" -> "<<receiver<<":";
			cout<<"[IMAGE]"<<text;
			cout<<"[lIKES : "<<likes<<"]"<<endl;
		}
		string gettype(){
			return "IMAGE";
		}
};
class Filemessage: public Message{
	public:
	Filemessage(string s,string r,string t,string ti){
		sender =s;
		receiver=r;
		text=t;
		time=ti;
		likes=0;
	}
	void show(int index){
		cout<<"["<<index<<"]";
			cout<<sender<<" -> "<<receiver<<":";
			cout<<"[FILE]"<<text;
			cout<<"[lIKES : "<<likes<<"]"<<endl;
		}
		string gettype(){
			return "FILE";
		}
};
class Notification{
	string user;
	string text;
	public:
		Notification(){
			user="unknown";
			text="unknown";
		}
		Notification(string u,string t){
			user=u;
			text=t;
		}
		string getuser() { 
        return user; 
    }
    
    string gettext() { 
        return text; 
    }
		void show(){
			cout<<"Notification : "<<text<<endl;
		}
};
class Group{
	string groupname;
	vector<string> members;
	public:
		Group(){
			groupname="unknown";
		}
			Group(string n){
				groupname=n;
		}
		string getname(){
			return groupname;
		}
		bool addmember(string user){
			for(int i=0;i<members.size();i++){
				if(members[i]==user){
					cout<<"User "<<user<<" is already a member of this group"<<endl;
					return false;
				}
			}
			members.push_back(user);
			return true;
		}
		vector<string> getmembers(){
			return members;
		}
		void showmembers(){
			cout<<endl;
			cout<<"----Group Members----"<<endl;
			for(int i=0;i<members.size();i++){
				cout<<i+1<<"."<<members[i]<<endl;
			}
		}
};
class Chatsystem{
	vector<User> users;
	vector<Message*> messages;
	vector<Group> groups;
	vector<Notification> notifications;
	public:
		~Chatsystem(){
			for(int i=0;i<messages.size();i++){
				delete messages[i];
			}
		}
		vector<User>& getuser(){
			return users;
		}
		string getcurrenttime(){
			time_t now=time(0);
			string t=ctime(&now);
			if(!t.empty()&&t[t.length()-1]=='\n'){
				t.erase(t.length()-1);
			}
			return t;
		}
	void adduser(string name){
		for(int i=0;i<users.size();i++){
			if(users[i].getname()==name){
				return;
			}
		}
		users.push_back(User(name));
	}
	void showusers(){
		cout<<endl;
		cout<<"All Users : "<<endl;
		for(int i=0;i<users.size();i++){
			cout<<users[i].getname()<<" - ";
			if (users[i].isonline()){
				cout<<"Online";
			}
			else{
				cout<<"Offline";
			}
			cout<<endl;
		}
	}
	void addnotifications(string user,string text){
		notifications.push_back(Notification(user,text));
	}
	void shownotifications(string currentuser){
		cout<<endl;
		cout<<"Notifications: "<<endl;
		bool found=false;
		for(int i=0; i<notifications.size();i++){
			if(notifications[i].getuser()==currentuser){
				notifications[i].show();
				notifications.erase(notifications.begin() + i);
                i--;
				found=true;
			}
		}
		if(!found){
			cout<<"No Notifications!"<<endl;
		}
	}
	void sendmessage(string s,string r,string text){
		adduser(r);
		messages.push_back(new Textmessage(s,r,text,getcurrenttime()));
		addnotifications(r,"New message from "+s);
		savealldata();
		cout<<"Message sent!"<<endl;
	}
	void sendimage(string s,string r,string image){
		adduser(r);
		messages.push_back(new Imagemessage(s,r,image,getcurrenttime()));
		addnotifications(r,"New message from "+s);
		savealldata();
		cout<<"Message sent"<<endl;
	}
	void sendfile(string s,string r,string file){
		adduser(r);
		messages.push_back(new Filemessage(s,r,file,getcurrenttime()));
		addnotifications(r,"New message from "+s);
		savealldata();
		cout<<"Message sent"<<endl;
	}
	void showchats(string currentuser){
		cout<<endl;
		cout<<"---------"<<endl;
		cout<<"| CHATS |"<<endl;
		cout<<"---------"<<endl;
		bool found=false;
		for(int i=0;i<messages.size();i++){
			if(messages[i]->getsender()==currentuser||messages[i]->getreceiver()==currentuser){
				messages[i]->show(i);
				found=true;
			}
		}
		if(!found){
			cout<<"No chats found!"<<endl;
		}
	}
	void searchmessage(string word){
		cout<<endl;
		cout<<"Searched Chats"<<endl;
		bool found=false;
		for(int i=0;i<messages.size();i++){
			if(messages[i]->gettext().find(word) !=string::npos){
				messages[i]->show(i);
				found=true;
			}
		}
		if(!found){
			cout<<"No message found"<<endl;
		}
	}
	void deletemessage(int index){
		if(index>=0&&index<messages.size()){
			delete messages[index];
			messages.erase(messages.begin()+index);
			savealldata();
			cout<<"Message Deleted!"<<endl;
		}
		else{
			cout<<"Invalid Index!"<<endl;
		}
	}
	void editmessage(int index,string text){
		if(index>=0&&index<messages.size()){
			messages[index]->edit(text);
			savealldata();
			cout<<"Message Edited!"<<endl;
		}
		else{
			cout<<"Invalid Index!"<<endl;
		}
	}
	void likemessage(int index){
		if(index>=0&&index<messages.size()){
			messages[index]->like();
			savealldata();
			cout<<"Message Liked"<<endl;
		}
		else{
			cout<<"Invalid Index"<<endl;
		}
	}
	void showmostlikes(){
		if(messages.size()==0){
			cout<<"No Messages!"<<endl;
			return;
		}
		int maxlikes= messages[0]->getlikes();
		int index=0;
		for(int i=0;i<messages.size();i++){
			if(messages[i]->getlikes()>maxlikes){
				maxlikes=messages[i]->getlikes();
				index=i;
			}
		}
		cout<<endl;
		cout<<"Most Liked Message: "<<endl;
		 messages[index]->show(index);
	}
	void creategroup(string name){
		groups.push_back(Group(name));
		savealldata();
		cout<<"Group Created!"<<endl;
	}
	void addMember(string groupName, string user) {
    adduser(user);
    for (int i = 0; i < groups.size(); i++) {
        if (groups[i].getname() == groupName) {
        	 if (groups[i].addmember(user)) { 
                savealldata();
                cout << "Member Added!"<<endl;
			}
			return;
		}
	}
	cout<<"Group Not Found!"<<endl;
	}
	void showgroups(){
		cout<<endl;
		cout<<"Groups: "<<endl;
		if(groups.size()==0){
			cout<<"No Groups!"<<endl;
			return;
		}
		for(int i=0;i<groups.size();i++){
			cout<<i+1<<"."<<groups[i].getname()<<endl;
		}
	}
	void showMembers(string groupName) {
        for (int i = 0; i < groups.size(); i++) {
            if ( groups[i].getname()== groupName){
                groups[i].showmembers();
                return;
            }
        }
        cout << "Group Not Found!\n";
    }
    void sendGroupMessage(string sender,string groupName,string text){
        for (int i = 0; i < groups.size(); i++) {
            if (groups[i].getname()== groupName) {
                vector<string> members =groups[i].getmembers();
                for (int j = 0;j < members.size();j++){
                    if (members[j] != sender) {
                        messages.push_back(new Textmessage(sender,members[j],"[GROUP: "+groupName+"] "+text,getcurrenttime()));
                        addnotifications(members[j],"Group message from " + sender);
                    }
                }

        savealldata();
                cout << "Group Message Sent!\n";
                return;
            }
        }
        cout << "Group Not Found!\n";
    }
    void clearChats() {
    	for(int i=0;i<messages.size();i++){
    		delete messages[i];
		}
        messages.clear();
        savealldata();
        cout << "All Chats Cleared!\n";
    }
    void savealldata() {
        ofstream file("chat.txt");
        for (int i = 0; i < users.size(); i++) {
            file << "USER|"<< users[i].getname()<< endl;
        }
        for (int i = 0; i < messages.size(); i++) {
            file << "MESSAGE|"<< messages[i]->getsender()<< "|"<< messages[i]->getreceiver()<< "|"<< messages[i]->gettext()<< "|"<< messages[i]->gettype()<< "|"<< messages[i]->gettime()<< "|"<< messages[i]->getlikes()<< endl;
        }
        for (int i = 0; i < groups.size(); i++) {
            file << "GROUP|"<< groups[i].getname()<< endl;
            vector<string> members =groups[i].getmembers();
            for (int j = 0; j < members.size(); j++) {
                file << "MEMBER|"<< groups[i].getname()<< "|"<< members[j]<< endl;
            }
        }
        for (int i = 0; i < notifications.size(); i++) {
            file << "NOTIFICATION|"<< notifications[i].getuser()<< "|"<< notifications[i].gettext()<< endl;
        }
        file.close();
    }
      void loadalldata() {
        ifstream file("chat.txt");
        if (!file)
            return;
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string type;
            getline(ss, type, '|');
            if (type == "USER") {
                string name;
                getline(ss, name);
                users.push_back(User(name));
            }
            else if (type == "MESSAGE") {
                string sender;
                string receiver;
                string text;
                string msgType;
                string time;
                string likesStr;
                getline(ss, sender, '|');
                getline(ss, receiver, '|');
                getline(ss, text, '|');
                getline(ss, msgType, '|');
                getline(ss, time, '|');
                getline(ss, likesStr);
                Message* msg;
                if(msgType=="TEXT"){
                	msg=new Textmessage(sender,receiver,text,time);
				}
				else if(msgType=="IMAGE"){
					msg=new Imagemessage(sender,receiver,text,time);
				}
				else{
					msg=new Filemessage(sender,receiver,text,time);
				}
                stringstream convert(likesStr);
                int likes;
                convert >> likes;
                msg->setlikes(likes);
                messages.push_back(msg);
            }
            else if (type == "GROUP") {
                string groupName;
                getline(ss, groupName);
                groups.push_back(Group(groupName));
            }
            else if (type == "MEMBER") {
                string groupName;
                string member;
                getline(ss, groupName, '|');
                getline(ss, member);
                for (int i = 0; i < groups.size(); i++) {
                    if (groups[i].getname()== groupName){
                        groups[i].addmember(member);
                    }
                }
            }
            else if (type == "NOTIFICATION") {
                string user;
                string text;
                getline(ss, user, '|');
                getline(ss, text);
                notifications.push_back(Notification(user, text));
            }
        }
        file.close();
    }
};
int main(){
	Chatsystem chat;
	chat.loadalldata();
	string currentuser;
	cout<<"     ========================="<<endl;
	cout<<"     ||CHAT MANAGMENT SYSTEM||"<<endl;
	cout<<"     ========================="<<endl;
	cout<<"Enter username: ";
	getline(cin,currentuser);
	chat.adduser(currentuser);
	for(int i=0;i<chat.getuser().size();i++){
		if(chat.getuser()[i].getname()==currentuser){
			chat.getuser()[i].setonline(true);
		}
	}
	int choice;
	string receiver;
	string text;
	string file;
	string groupname;
	int index;
	do{
		cout<<"=========MENU========="<<endl;
		cout << "1. Send Message"<<endl;
        cout << "2. View Chats"<<endl;
        cout << "3. Search Message"<<endl;
        cout << "4. Delete Message"<<endl;
        cout << "5. Edit Message"<<endl;
        cout << "6. Send Image"<<endl;
        cout << "7. Send File"<<endl;
        cout << "8. Create Group"<<endl;
        cout << "9. Add Member To Group"<<endl;
        cout << "10. Send Group Message"<<endl;
        cout << "11. Show Groups"<<endl;
        cout << "12. Show Group Members"<<endl;
        cout << "13. Like Message"<<endl;
        cout << "14. Show Notifications"<<endl;
        cout << "15. Show Users"<<endl;
        cout << "16. Clear All Chats"<<endl;
        cout << "17. Show Most Liked Message"<<endl;
        cout << "18. Exit"<<endl;
        cout<<"Enter Choice : ";
        cin>>choice;
        if (choice == 1) {
            cin.ignore();
            cout << "Receiver: ";
            getline(cin, receiver);
            cout << "Message: ";
            getline(cin, text);
            chat.sendmessage(currentuser,receiver,text);
        }
        else if (choice == 2) {
            chat.showchats(currentuser);
        }
        else if (choice == 3) {
            cin.ignore();
            cout << "Search Word: ";
            getline(cin, text);
            chat.searchmessage(text);
        }
        else if (choice == 4) {
            cout << "Index: ";
            cin >> index;
            chat.deletemessage(index);
        }
        else if (choice == 5) {
            cout << "Index: ";
            cin >> index;
            cin.ignore();
            cout << "New Message: ";
            getline(cin, text);
            chat.editmessage(index, text);
        }
        else if (choice == 6) {
            cin.ignore();
            cout << "Receiver: ";
            getline(cin, receiver);
            cout << "Image Name: ";
            getline(cin, file);
            chat.sendimage(currentuser,receiver,file);
        }
        else if (choice == 7) {
            cin.ignore();
            cout << "Receiver: ";
            getline(cin, receiver);
            cout << "File Name: ";
            getline(cin, file);
            chat.sendfile(currentuser,receiver,file);
        }
        else if (choice == 8) {
            cin.ignore();
            cout << "Group Name: ";
            getline(cin, groupname);
            chat.creategroup(groupname);
        }
        else if (choice == 9) {
            cin.ignore();
            cout << "Group Name: ";
            getline(cin, groupname);
            cout << "User Name: ";
            getline(cin, receiver);
            chat.addMember(groupname,receiver);
        }
        else if (choice == 10) {
            cin.ignore();
            cout << "Group Name: ";
            getline(cin, groupname);
            cout << "Message: ";
            getline(cin, text);
            chat.sendGroupMessage(currentuser,groupname,text);
        }
        else if (choice == 11) {
            chat.showgroups();
        }
        else if (choice == 12) {
            cin.ignore();
            cout << "Group Name: ";
            getline(cin, groupname);
            chat.showMembers(groupname);
        }
        else if (choice == 13) {
            cout << "Message Index: ";
            cin >> index;
            chat.likemessage(index);
        }
        else if (choice == 14) {
            chat.shownotifications(currentuser);
        }
        else if (choice == 15) {
            chat.showusers();
        }
        else if (choice == 16) {
            chat.clearChats();
        }
        else if (choice == 17) {
            chat.showmostlikes();
        }
        else if (choice == 18) {
            cout << "Goodbye!\n";
        }
        else {
            cout << "Invalid Choice!\n";
        }

    } while (choice != 18);

    return 0;
}

