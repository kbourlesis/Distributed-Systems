package com.konstantinos.katanemimena.hotel;

import java.rmi.*;
import java.rmi.server.*;

public class CallbackClientImpl extends UnicastRemoteObject implements CallbackClientInterface {

   public CallbackClientImpl() throws RemoteException {
      super();
   }

   public void notifyMe(String message) {

      String returnMessage = "There are " + message;
      System.out.println(returnMessage);
   }

}
