package com.konstantinos.katanemimena.hotel;

import java.util.*;

public interface Hotel_Interface extends java.rmi.Remote{

    public Set<Room> list () throws java.rmi.RemoteException;

    public String book(String roomType, int reservedRooms, String reservationName) throws java.rmi.RemoteException;

    public Map<String, ArrayList<Reservation>> guests() throws java.rmi.RemoteException;

    public String cancel(String roomType, int canceledRooms, String reservationName) throws java.rmi.RemoteException;

    public int getRoomPrice(String roomType) throws java.rmi.RemoteException;

    public void addToWaitingList(String roomType, CallbackClientInterface clientInterface) throws java.rmi.RemoteException;

}
