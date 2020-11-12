package com.konstantinos.katanemimena.hotel;

import java.io.Serializable;

public class Room implements Serializable {

    private int availableRooms, price;
    private String type;

    public Room(String type, int availableRooms, int price) {
        this.type = type;
        this.availableRooms = availableRooms;
        this.price = price;
    }

    public String getType(){
        return type;
    }

    public int getPrice(){
        return price;
    }

    public int getAvailableRooms(){
        return availableRooms;
    }

    public void setAvailableRooms(int availableRooms) {
        this.availableRooms = availableRooms;
    }

    public void print_roomInfos(){
        System.out.println("Type: "+ type +", Available rooms: "+ availableRooms +", Price: "+ price +"€/night.");
    }

}
