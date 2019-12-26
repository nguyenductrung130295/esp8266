import { Injectable } from '@angular/core';
import { AngularFireAuth } from '@angular/fire/auth';
import { auth } from 'firebase/app';
import { FirebaseAuth } from '@angular/fire';

@Injectable({
  providedIn: 'root'
})
export class AuthenticationService {

  displayName: string;
  photoURL: string;
  constructor(public afAuth: AngularFireAuth) { }

  getAuth(): FirebaseAuth {
    return this.afAuth.auth;
  }

  login() {
    this.getAuth().signInWithPopup(new auth.GoogleAuthProvider());
  }

  logout() {
    this.getAuth().signOut();
  }
}
