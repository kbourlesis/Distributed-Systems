package com.konstantinos.katanemimena.hotel;

import java.io.Serializable;

public class Reservation implements Serializable {

    private String roomType, customerName;
    private int reservedRooms;

    public Reservation(String roomType, String customerName, int reservedRooms) {
        this.roomType = roomType;
        this.customerName = customerName;
        this.reservedRooms = reservedRooms;
    }

    public void print_Reservation(){
        System.out.print("Room type: "+ getRoomType() +
                ", Reserved rooms: "+ getReservedRooms());
    }

    public String getRoomType() {

        return roomType;
    }

    public String getCustomerName() {

        return customerName;
    }

    public int getReservedRooms() {

        return reservedRooms;
    }

    public void setRoomType(String roomType) {

        this.roomType = roomType;
    }

    public void setCustomerName(String customerName) {

        this.customerName = customerName;
    }

    public void setReservedRooms(int reservedRooms) {

        this.reservedRooms = reservedRooms;
    }
}
