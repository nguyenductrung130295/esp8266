import { Component } from '@angular/core';
import { AngularFirestore } from '@angular/fire/firestore';//database firestore
import { AngularFireDatabase } from '@angular/fire/database';// database realtime

import { Observable } from 'rxjs';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  items: Observable<any[]>;
  title = 'front-angular';
  // constructor(db: AngularFirestore) {
  //   this.items = db.collection('items').valueChanges();
  // }

  // inject firebaseDatabase
  constructor(db: AngularFireDatabase) {
    this.items = db.list('items').valueChanges();
    console.log(this.items);
  }
}
