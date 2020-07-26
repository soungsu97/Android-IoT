package com.example.hellofirebasedbc3;

import android.os.Bundle;
import android.widget.ListView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import com.google.firebase.database.ChildEventListener;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;

public class MainListView extends AppCompatActivity {

    FirebaseDatabase db = FirebaseDatabase.getInstance(); //Firebase의 내장 객체를 선언
    DatabaseReference myRef = db.getReference("logDHT");

    ListView list;
    ListViewAdapter adapter;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main_listview);

        list = (ListView)findViewById(R.id.lvItem);
        adapter = new ListViewAdapter();
        list.setAdapter(adapter);  //리스트 뷰에 Adapter를 세팅

        myRef.addChildEventListener(new ChildEventListener() { //데이터베이스의 값이 변경 될때마다 실행
            @Override
            public void onChildAdded(@NonNull DataSnapshot snapshot, @Nullable String previousChildName) {   // 값이 추가 될때마다 실행
                String data1 = snapshot.child("temperature").getValue().toString();  //Firebase의 값을 가져옴
                String data2 = snapshot.child("humidity").getValue().toString();
                String data3 = snapshot.child("date").getValue().toString();
                adapter.addItem(data1 + "℃", data2 + "%", data3);   //Adapter에 가져온 값을 붙임
                adapter.notifyDataSetChanged(); //리스트 뷰를 수동으로 갱신
            }

            @Override
            public void onChildChanged(@NonNull DataSnapshot snapshot, @Nullable String previousChildName) {

            }

            @Override
            public void onChildRemoved(@NonNull DataSnapshot snapshot) {

            }

            @Override
            public void onChildMoved(@NonNull DataSnapshot snapshot, @Nullable String previousChildName) {

            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {

            }
        });
    }
}
