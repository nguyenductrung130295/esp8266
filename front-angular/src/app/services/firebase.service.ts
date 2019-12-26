import { Injectable } from '@angular/core';

// import { AngularFirestore } from '@angular/fire/firestore';//database firestore
import { AngularFireDatabase } from '@angular/fire/database'; // database realtime
import { Observable } from 'rxjs';
import { UrlService } from './url.service';


@Injectable({
  providedIn: 'root'
})
export class FirebaseService {
  database: AngularFireDatabase;
  url: UrlService;
  // items: Observable<any[]>;
  // led: Observable<any>;
  // constructor(db: AngularFirestore) {
  //   this.items = db.collection('items').valueChanges();
  // }

  // inject firebaseDatabase
  constructor(db: AngularFireDatabase, private urlService: UrlService) {
    this.database = db;
    this.url = this.urlService;
  }

  getObject(path: string): Observable<any> {
    console.log('request get object: ' + path);
    return this.database.object(path).valueChanges();
  }

  getListValues(path: string): Observable<any[]> {
    console.log('request get list: ' + path);
    return this.database.list(path).valueChanges();
  }

  saveObject(path: string, object: any): void {
    console.log('request save object:' + path);
    this.database.object(path).set(object);
  }

  updateObject(path: string, object: any): void {
    console.log('request update object: ' + path);
    this.database.object(path).update(object);
  }
}
