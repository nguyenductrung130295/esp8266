import { Component, OnInit } from '@angular/core';
import { AuthenticationService } from './services/authentication.service';
import { UrlService } from './services/url.service';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent implements OnInit {

  isLogging = false;
  constructor(private authService: AuthenticationService, private urlService: UrlService) {
  }

  ngOnInit(): void {
    this.isLogging = true;
    this.authService.afAuth.user.subscribe(value => {
      if (!value) {
        this.urlService.setUserId(null);
      } else {
        this.authService.photoURL = value.photoURL;
        this.authService.displayName = value.displayName;
        this.urlService.setUserId(value.uid);
      }
    });
    for (let i = 0; i <= 5000; i++) {
      if (!this.urlService.userId) {
        this.isLogging = false;
        break;
      }
    }
  }
}
