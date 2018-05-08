#include <bits/stdc++.h>
#define MAX_PACKETS 5
#define PACKET_SIZE 1024
#define ERROR_RATE 0.05 // 5% Error Rate
#define WINDOW_SIZE 3

using namespace std;

enum Packet_type {
    Data,
    Acknowledgment
};


class Packet {
    public:
        int length;
        int id;
        int type;
        Packet(int type, int id, int length) {
            this->type = type;
            this->id = id;
            this->length = length;
        }
};

void Print(Packet p, bool error=false) {
    if(error){
        cout<<"Packet [seq_no="<<p.id<<"]["<<PACKET_SIZE<<"B] lost.\n";
    }else if (p.type == Data) {
        cout<<"Packet [seq_no="<<p.id<<"]["<<PACKET_SIZE<<"B] transmitted.\n";        
    }else {
        cout<<"Acknowledgment [seq_no="<<p.id<<"] recieved.\n";        
    }
}

bool sendPacket(int seq, bool err=false) {
    Packet p(Data, seq, PACKET_SIZE);
    Print(p, err);
    bool error = (rand()%2) <= ERROR_RATE ? true : false;
    return error;
}

void sendAcknowledment(int seq) {
    Packet p(Acknowledgment, seq, PACKET_SIZE);
    Print(p);
}

int main() {
  srand(time(NULL));
  bool error[WINDOW_SIZE];
  int start=1;
  while(true){
    for(int i=start; i<=min(MAX_PACKETS, start+WINDOW_SIZE); i++)
      error[i-start] = sendPacket(i);
    for(int i=0; i<=min(WINDOW_SIZE, MAX_PACKETS-start); i++)
      if(error[i]) sendPacket(start+i, true);
      else sendAcknowledment(start+i);
    for(int i=0; i<=min(WINDOW_SIZE, MAX_PACKETS-start); i++)
      if(error[i]) sendPacket(start+i);
    for(int i=0; i<=min(WINDOW_SIZE, MAX_PACKETS-start); i++)
      if(error[i]) sendAcknowledment(start+i);
    start = min(MAX_PACKETS, start+WINDOW_SIZE) + 1;
    if(start > MAX_PACKETS) break;
  }
  return 0;
}
