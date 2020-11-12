package com.konstantinos.katanemimena.hotel;

import java.util.*;

public class Hotel_Implementation extends java.rmi.server.UnicastRemoteObject implements Hotel_Interface{

    Set<Room> roomList = new LinkedHashSet<Room>();
    List<Reservation> reservationList = new ArrayList<>();
    Map<String, ArrayList<CallbackClientInterface>> waitingLists = new HashMap();

    public Hotel_Implementation() throws java.rmi.RemoteException{
        super();

        roomList.add(new Room("A", 30, 50));
        roomList.add(new Room("B", 45, 70));
        roomList.add(new Room("C", 25, 80));
        roomList.add(new Room("D", 10, 120));
        roomList.add(new Room("E", 5, 150));

        waitingLists.put("A", new ArrayList<>());
        waitingLists.put("B", new ArrayList<>());
        waitingLists.put("C", new ArrayList<>());
        waitingLists.put("D", new ArrayList<>());
        waitingLists.put("E", new ArrayList<>());

    }

    public Set<Room> list() throws java.rmi.RemoteException{
        return roomList;
    }

    public String book(String roomType, int reservedRooms, String reservationName) throws java.rmi.RemoteException{

        int newAvailableRooms, totalCost = 0;
        Room room;

        room = getRoom(roomType);
        newAvailableRooms = room.getAvailableRooms() - reservedRooms;

        if ( (newAvailableRooms > -1) && (newAvailableRooms != room.getAvailableRooms()) ){

            reservationList.add(new Reservation(roomType, reservationName, reservedRooms));
            room.setAvailableRooms(newAvailableRooms);
            totalCost += reservedRooms * room.getPrice();

            return "Reservation succeeded!\nTotal cost is " + totalCost +" €.";

        }else{
            if(room.getAvailableRooms() == 0)
                return "Reservation failed...\nTotal cost is " + totalCost +" €.\nThere are no rooms of this type available. Do you want to register yourself on our waiting list?\nThis way you are going to be notified when a room is available again.(Y/n)";
            else
                return "Reservation failed...\nThere are "+ room.getAvailableRooms() +" rooms available. Do you want to reserve them?";
        }

    }

    public Map<String, ArrayList<Reservation>> guests() throws java.rmi.RemoteException{

        Map<String, ArrayList<Reservation>> customersReservations = new HashMap<>();
        String name;

        for (Reservation reservation: reservationList) {

            name = reservation.getCustomerName();
            if (customersReservations.get(name) == null){

                ArrayList<Reservation> customerReservationList = new ArrayList<Reservation>();
                customerReservationList.add(reservation);
                customersReservations.put(name,customerReservationList);

            }else{
                customersReservations.get(name).add(reservation);
            }
        }

        return customersReservations;

    }

    public String cancel(String roomType, int canceledRooms, String reservationName) throws java.rmi.RemoteException{

        Map<String, ArrayList<Reservation>> customersReservations = guests();
        ArrayList<Reservation> reservations = customersReservations.get(reservationName);

        if(customersReservations.get(reservationName) == null)
            return "There are no reservations to be canceled on name: "+ reservationName +".\n";

        String msg = "";
        int ReservationFound = 0;

        for (Reservation reservation: reservations) {

            if(reservation.getReservedRooms() == canceledRooms && reservation.getRoomType().equals(roomType) && ReservationFound == 0){
                reservationList.remove(reservation);
                ReservationFound = 1;
            }else{
                msg += "Room type: "+ reservation.getRoomType() +", Reserved rooms: "+ reservation.getReservedRooms()+", Total reservation cost: "+ reservation.getReservedRooms() * getRoomPrice(reservation.getRoomType())+".\n";
            }

        }

        if(ReservationFound == 0)
            msg = "There is no such reservation to be canceled.\nRoom type: "+ roomType +", Reserved rooms: "+ canceledRooms +".\n\n"+ reservationName +"'s reservations:\n" + msg;
        else{
            msg = reservationName +"'s active reservations: \n"+ msg;

            Room room = null;
            for (Room rm : roomList) {
                if (rm.getType().equals(roomType)){
                    room = rm;
                }
            }
            room.setAvailableRooms(room.getAvailableRooms()+canceledRooms);

            String notify = "";
            for (CallbackClientInterface clientI: waitingLists.get(roomType)){
                notify = String.valueOf(room.getAvailableRooms()) + " available rooms of type " + roomType +".";
                clientI.notifyMe(notify);
            }
        }

        return msg;

    }

    public void addToWaitingList(String roomType, CallbackClientInterface clientInterface) throws java.rmi.RemoteException{

        waitingLists.get(roomType).add(clientInterface);

    }

    public int getRoomPrice(String roomType) throws java.rmi.RemoteException{

        for (Room room: roomList) {
            if(room.getType().equals(roomType))
                return room.getPrice();
        }

        throw new RuntimeException("No room of this type found.");
    }

    Room getRoom(String type){

        for (Room room: roomList) {

            if (room.getType().equals(type)){

                return room;

            }
        }

        throw new RuntimeException("No room of this type found.");

    }

}
