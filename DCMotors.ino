void forward(){
  digitalWrite(RF.dir1Pin, HIGH);
  digitalWrite(RF.dir2Pin, LOW);
  digitalWrite(RF.dir1Pin, HIGH);
  digitalWrite(RF.dir2Pin, LOW);
  digitalWrite(LF.dir1Pin, HIGH);
  digitalWrite(LF.dir2Pin, LOW);
  digitalWrite(RR.dir1Pin, HIGH);
  digitalWrite(RR.dir2Pin, LOW);
  digitalWrite(LR.dir1Pin, HIGH);
  digitalWrite(LR.dir2Pin, LOW);
}

void off(){
  digitalWrite(RF.dir1Pin, LOW);
  digitalWrite(RF.dir2Pin, LOW);
  digitalWrite(LF.dir1Pin, LOW);
  digitalWrite(LF.dir2Pin, LOW);
  digitalWrite(RR.dir1Pin, LOW);
  digitalWrite(RR.dir2Pin, LOW);
  digitalWrite(LR.dir1Pin, LOW);
  digitalWrite(LR.dir2Pin, LOW);      
}

void aft(){
      digitalWrite(RF.dir1Pin, LOW);
      digitalWrite(RF.dir2Pin, HIGH);
      digitalWrite(LF.dir1Pin, LOW);
      digitalWrite(LF.dir2Pin, HIGH);
      digitalWrite(RR.dir1Pin, LOW);
      digitalWrite(RR.dir2Pin, HIGH);
      digitalWrite(LR.dir1Pin, LOW);
      digitalWrite(LR.dir2Pin, HIGH);     
}

void left(){
      digitalWrite(RF.dir1Pin,HIGH);
      digitalWrite(RF.dir2Pin, LOW);
      digitalWrite(LF.dir1Pin, LOW);
      digitalWrite(LF.dir2Pin, HIGH);
      digitalWrite(RR.dir1Pin, HIGH);
      digitalWrite(RR.dir2Pin, LOW);
      digitalWrite(LR.dir1Pin, LOW);
      digitalWrite(LR.dir2Pin, HIGH);      
}

void right(){
      digitalWrite(RF.dir1Pin, LOW);
      digitalWrite(RF.dir2Pin, HIGH);
      digitalWrite(LF.dir1Pin, HIGH);
      digitalWrite(LF.dir2Pin, LOW);
      digitalWrite(RR.dir1Pin, LOW);
      digitalWrite(RR.dir2Pin, HIGH);
      digitalWrite(LR.dir1Pin, HIGH);
      digitalWrite(LR.dir2Pin, LOW);      
}

void tranLeft(){
      digitalWrite(RF.dir1Pin, HIGH);
      digitalWrite(RF.dir2Pin, LOW);
      digitalWrite(LF.dir1Pin, LOW);
      digitalWrite(LF.dir2Pin, HIGH);
      digitalWrite(RR.dir1Pin, LOW);
      digitalWrite(RR.dir2Pin, HIGH);
      digitalWrite(LR.dir1Pin, HIGH);
      digitalWrite(LR.dir2Pin, LOW);      
}

void tranRight(){
      digitalWrite(RF.dir1Pin, LOW);
      digitalWrite(RF.dir2Pin, HIGH);
      digitalWrite(LF.dir1Pin,HIGH);
      digitalWrite(LF.dir2Pin, LOW);
      digitalWrite(RR.dir1Pin, HIGH);
      digitalWrite(RR.dir2Pin, LOW);
      digitalWrite(LR.dir1Pin, LOW);
      digitalWrite(LR.dir2Pin, HIGH);      
}
