# Chat Management System

**Chat Management System is a console-based C++ program that lets users exchange text, image and file messages and organize conversations in groups.** It saves all chats, users and notifications to a plain text file, so nothing is lost when the program closes.

## Requirements

| Item | Requirement |
|------|-------------|
| **Operating System** | Windows 10/11, Linux, or macOS |
| **Language** | C++11 or newer |
| **Compiler** | g++ (GCC) 7.0 or newer (or any C++11-compatible compiler) |
| **Libraries** | C++ Standard Library only (`iostream`, `vector`, `fstream`, `sstream`, `ctime`) |

## Installation

1. **Clone** the repository: `git clone https://github.com/naverasajjad11-ray/chat-management-system.git`
2. **Enter** the project folder: `cd chat-management-system`
3. **Compile** the program: `g++ chatmanpractice.cpp -o chatsystem`

To start it, run `./chatsystem` (Linux/macOS) or `chatsystem.exe` (Windows).

## Minimal Working Example

Run the program, then type the following inputs in order:

```
Enter username: Navera
Enter Choice : 1
Receiver: Ali
Message: Hello Ali
Enter Choice : 2
Enter Choice : 18
```

Expected output after choosing `2` (View Chats):

```
---------
| CHATS |
---------
[0]Navera -> Ali : Hello Ali[LIKES : 0]
```

## Features

- Send text messages, images and files
- Create groups, add members, send group messages
- Search, edit, delete and like messages
- Notifications for new messages
- Automatic saving to `chat.txt`

## Project Structure

| Class | Purpose |
|-------|---------|
| `Person` / `User` | Stores user name and online status (inheritance) |
| `Message` | Abstract base class for all messages |
| `Textmessage`, `Imagemessage`, `Filemessage` | Message types (polymorphism) |
| `Group`, `Notification` | Group members and user notifications |
| `Chatsystem` | Main controller: handles all operations and file saving |

## Known Limitations

- Images and files are stored as names only (nothing is actually uploaded).
- Do not use the `|` character in messages, because it is used as the separator in `chat.txt`.

## Author

Navera Sajjad
Sania Arham
Ayesha Nasreen
Areeba Umar
 BS Computer Science
 University of Kamalia
