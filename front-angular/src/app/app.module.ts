import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { AngularFireModule } from '@angular/fire';
import { AngularFirestoreModule } from '@angular/fire/firestore';
import { AngularFireStorageModule } from '@angular/fire/storage';
import { AngularFireAuthModule } from '@angular/fire/auth';
import { environment } from '../environments/environment';
import { AngularFireDatabaseModule } from '@angular/fire/database';
import { ButtonComponent } from './common/button/button.component';
import { CardComponent } from './common/card/card.component';
import { ChickenFarmComponent } from './chicken-farm/chicken-farm.component';
import { FirebaseService } from './services/firebase.service';
import { UrlService } from './services/url.service';

@NgModule({
  declarations: [
    AppComponent,
    ButtonComponent,
    CardComponent,
    ChickenFarmComponent
  ],
  imports: [
    BrowserModule,
    AngularFireModule.initializeApp(environment.firebase),
    AngularFirestoreModule, // imports firebase/firestore, only needed for database features
    AngularFireDatabaseModule,
    AngularFireAuthModule, // imports firebase/auth, only needed for auth features,
    AngularFireStorageModule, // imports firebase/storage only needed for storage features
    AppRoutingModule
  ],
  providers: [FirebaseService, UrlService],
  bootstrap: [AppComponent]
})
export class AppModule { }
