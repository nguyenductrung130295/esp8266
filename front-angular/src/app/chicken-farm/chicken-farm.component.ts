import { Component, OnInit, OnDestroy } from '@angular/core';
import { FirebaseService } from '../services/firebase.service';
import { Observable, Subscription } from 'rxjs';
import { UrlService } from '../services/url.service';
import { EatAndDrinkAndLight } from '../model/models';
import { AuthenticationService } from '../services/authentication.service';

@Component({
  selector: 'app-chicken-farm',
  templateUrl: './chicken-farm.component.html',
  styleUrls: ['./chicken-farm.component.css']
})
export class ChickenFarmComponent implements OnInit, OnDestroy {

  // box01: EatAndDrinkAndLight;
  itemsObs: Subscription;
  items: EatAndDrinkAndLight[];
  constructor(private firebaseService: FirebaseService, private url: UrlService) {
  }

  ngOnInit() {
    // this.firebaseService.getObject(this.url.groupItemOfDeviceUrl('smart01', 'group01')).subscribe(value => {
    //   console.log(value);
    // });
    this.itemsObs = this.firebaseService.getListValues(this.url.datasOfDeviceUrl('smart01')).subscribe(value => {
      this.items = value;
    });

  }

  feedChicken(item: EatAndDrinkAndLight) {
    if (item.eat) {
      item.feeding = !item.feeding;
      this.firebaseService.updateObject(this.url.groupItemOfDeviceUrl('smart01', item.key), item);
    }
  }

  turnOnOffLight(item: EatAndDrinkAndLight) {
    item.light = !item.light;
    this.firebaseService.updateObject(this.url.groupItemOfDeviceUrl('smart01', item.key), item);
  }

  ngOnDestroy(): void {
    this.itemsObs.unsubscribe();
    // throw new Error("Method not implemented.");
  }
}
