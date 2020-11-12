package com.konstantinos.katanemimena.hotel;

public interface CallbackClientInterface extends java.rmi.Remote{

    public void notifyMe(String message) throws java.rmi.RemoteException;

}
