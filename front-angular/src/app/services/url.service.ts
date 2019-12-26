import { Injectable } from '@angular/core';

@Injectable({
  providedIn: 'root'
})
export class UrlService {

  OWNS = 'owns';
  DATA = 'datas';
  userId: string;

  constructor() { }

  setUserId(userId: string): void {
    this.userId = userId;
  }

  userUrl(): string {
    if (!this.userId) {
      throw new Error('user is null. please login to use.');
    }
    return this.userId;
  }

  ownsOfUserUrl(): string {
    return this.userUrl() + '/' + this.OWNS;
  }

  deviceUrl(deviceKey: string): string {
    return this.ownsOfUserUrl() + '/' + deviceKey;
  }

  datasOfDeviceUrl(deviceKey: string): string {
    return this.deviceUrl(deviceKey) + '/' + this.DATA;
  }

  groupItemOfDeviceUrl(deviceKey: string, groupKey: string): string {
    return this.datasOfDeviceUrl(deviceKey) + '/' + groupKey;
  }
}
