package com.konstantinos.katanemimena.hotel;

import java.net.MalformedURLException;
import java.rmi.Naming;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.util.*;

public class Hotel_Client {

    public static void main(String[] args){

        try{
            if (args.length == 0){
                System.out.println("Usage: java Hotel_Client (list/book/guests/cancel) <remote machine> <room type> <rooms to be reserved> <your name-lastname>");
                System.exit(0);

            }else{
                String hostID = args[1];
                Hotel_Interface hInterface = (Hotel_Interface) Naming.lookup("rmi://"+hostID+":43862/HotelService");

                if(args[0].equals("list")){

                    if(args.length != 2){
                        System.out.println("Usage: list <remote machine>");
                        System.exit(0);
                    }

                    Set<Room> roomsList = hInterface.list();

                    for (Room room: roomsList) {
                        room.print_roomInfos();
                    }

                }else if(args[0].equals("book")){

                    if(args.length != 5){
                        System.out.println("Usage: book <remote machine> <room type> <rooms to be reserved> <your name-lastname>");
                        System.exit(0);
                    }

                    Scanner keyboard = new Scanner(System.in);
                    String input;
                    int roomsToBeReserved =  Integer.valueOf(args[3]);

                    while (true) {

                        String reservationStatus = hInterface.book(args[2], roomsToBeReserved, args[4]);

                        System.out.println(reservationStatus);
                        if(reservationStatus.contains("waiting")) {
                            input = keyboard.nextLine();

                            if (input.equalsIgnoreCase("yes") || input.equalsIgnoreCase("y")){
                                CallbackClientInterface callbackObj = new CallbackClientImpl();
                                hInterface.addToWaitingList(args[2], callbackObj);
                            }

                            break;

                        }else if (reservationStatus.contains("reserve")){
                            input = keyboard.nextLine();

                            if (input.equalsIgnoreCase("yes") || input.equalsIgnoreCase("y")) {
                                roomsToBeReserved = Integer.parseInt(reservationStatus.trim().split(" ")[3]);
                            }else{
                                break;
                            }

                        }else{
                            break;
                        }

                    }

                }else if(args[0].equals("guests")){

                    if(args.length != 2){
                        System.out.println("Usage: guests <remote machine>");
                        System.exit(0);
                    }

                    Map<String, ArrayList<Reservation>> customersReservations = hInterface.guests();
                    if(!customersReservations.isEmpty()) {
                        for (Map.Entry<String, ArrayList<Reservation>> customerReservations : customersReservations.entrySet()) {

                            System.out.println("\n"+ customerReservations.getKey());

                            for (Reservation reservation : customerReservations.getValue()) {

                                reservation.print_Reservation();
                                int price = hInterface.getRoomPrice(reservation.getRoomType());
                                System.out.println(", Total reservation cost: " + reservation.getReservedRooms() * price + ".");

                            }

                        }
                    }else
                        System.out.println("There are no guests.");

                }else if(args[0].equals("cancel")){

                    if(args.length != 5){
                        System.out.println("Usage: cancel <remote machine> <room type> <rooms to be canceled> <reservation name-lastname>");
                        System.exit(0);
                    }
                    int roomsToBeCanceled = Integer.valueOf(args[3]);
                    String reservationStatus = hInterface.cancel(args[2], roomsToBeCanceled, args[4]);

                    System.out.print(reservationStatus);

                }else {
                    System.out.println("Usage: java Hotel_Client (list/book/guests/cancel) <remote machine> <room type> <rooms to be reserved> <your name-lastname>");
                    System.exit(0);
                }

            }

        }
        catch (MalformedURLException murle){
            System.out.println();
            System.out.println("MalformedURLException");
            System.out.println(murle);
        }
        catch (RemoteException re) {
            System.out.println();
            System.out.println(
                    "RemoteException");
            System.out.println(re);
        }
        catch (NotBoundException nbe) {
            System.out.println();
            System.out.println(
                    "NotBoundException");
            System.out.println(nbe);
        }
        catch (
                java.lang.ArithmeticException
                        ae) {
            System.out.println();
            System.out.println(
                    "java.lang.ArithmeticException");
            System.out.println(ae);
        }
    }
}
