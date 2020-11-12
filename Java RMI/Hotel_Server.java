package com.konstantinos.katanemimena.hotel;

import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class Hotel_Server {

    public Hotel_Server(){

        try{
            Hotel_Interface hInterface = new Hotel_Implementation();
            Naming.rebind("rmi://localhost:43862/HotelService",  hInterface);
        }catch (Exception e){
            System.out.println("There is a problem -> " + e);
            e.printStackTrace();
        }

    }

    public static void main(String args[]) {

        try {
            startRegistry(43862);
        } catch (RemoteException e) {
            e.printStackTrace();
        }

        new Hotel_Server();

    }

    private static void startRegistry(int RMIPortNum)
            throws RemoteException {
        try {
            Registry registry = LocateRegistry.getRegistry(RMIPortNum);
            registry.list( );
            // This call will throw an exception
            // if the registry does not already exist
        }
        catch (RemoteException e) {
            // No valid registry at that port.
            Registry registry = LocateRegistry.createRegistry(RMIPortNum);
        }
    } // end startRegistry
}
