package com.example.hellofirebasedbc3;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.TextView;

import org.w3c.dom.Text;

import java.util.ArrayList;

public class ListViewAdapter extends BaseAdapter {
    ArrayList<ListViewItem> itemlist = new ArrayList<>();  //리스트 뷰의 목록을 배열로 받음
    ListViewAdapter(){}         //리스트뷰어댑터를 선언

    public int getCount() {return itemlist.size();}  // 리스트뷰 목록의 크기를 구하는 메소드

    public Object getItem(int i) {return itemlist.get(i);} // 리스트뷰 목록의 아이템을 가져옴

    public long getItemId(int i) {return i; }  // 리스트 목록의 번호를 가져옴

    public View getView(int i , View view, ViewGroup viewGroup){  //리스트뷰의 목록을 표시하기 위한 메소드

        final int pos = i;
        final Context c = viewGroup.getContext();

        if(view == null){
            LayoutInflater inflater = (LayoutInflater)c.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
            view = inflater.inflate(R.layout.listitem, viewGroup, false);
        }
        TextView tvHumi = (TextView)view.findViewById(R.id.tvHumi);
        TextView tvTemp = (TextView)view.findViewById(R.id.tvTemp);
        TextView tvTime = (TextView)view.findViewById(R.id.tvTime);

        ListViewItem listViewItem = itemlist.get(i);

        tvHumi.setText(listViewItem.getHumi());
        tvTemp.setText(listViewItem.getTemp());
        tvTime.setText(listViewItem.getTime());


        return view;
    }
    public void addItem(String temp, String humi, String time){ //리스트뷰 목록 추가
        ListViewItem lvitem = new ListViewItem();
        lvitem.setTemp(temp);
        lvitem.setHumi(humi);
        lvitem.setTime(time);

        itemlist.add(lvitem);
    }
}
